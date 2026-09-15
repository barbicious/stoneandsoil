#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

namespace gfx {
    Shader::~Shader() {
        glDeleteProgram(id);
    }

    void Shader::bind() const {
        glUseProgram(id);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    void Shader::setMat4(const std::string_view& name, const glm::mat4& value) const {
        glUniformMatrix4fv(glGetUniformLocation(id, name.data()), 1, false, glm::value_ptr(value));
    }

    void Shader::setI32(const std::string_view& name, i32 value) const {
        glUniform1i(glGetUniformLocation(id, name.data()), value);
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
            std::array < char, 512 > error_buffer{};
            glGetShaderInfoLog(shader, error_buffer.size(), nullptr, error_buffer.data());

            std::cerr << error_buffer.data() << std::endl;
        }

        return shader;
    }
} // gfx