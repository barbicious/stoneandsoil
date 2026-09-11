#include "shader.hpp"

#include <fstream>
#include <sstream>

namespace gfx {
    Shader::~Shader() {
        glDeleteProgram(id);
    }

    void Shader::bind() {
        glUseProgram(id);
    }

    void Shader::unbind() {
        glUseProgram(0);
    }

    u32 Shader::compileShader(Desc desc) {
        u32 shader{glCreateShader(desc.type)};

        std::ifstream file{desc.path};

        if (!file.is_open()) {
            std::cerr << "Failed to open shader file." << std::endl;
        }

        std::stringstream file_buffer{};

        file_buffer << file.rdbuf();

        std::string file_string{file_buffer.str()};
        const char* file_c_string{file_string.c_str()};

        glShaderSource(shader, 1, &file_c_string, nullptr);
        glCompileShader(shader);

        i32 success{};
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            std::array<char, 512> error_buffer{};
            glGetShaderInfoLog(shader, error_buffer.size(), nullptr, error_buffer.data());

            std::cerr << error_buffer.data() << std::endl;
        }

        return shader;
    }
} // gfx