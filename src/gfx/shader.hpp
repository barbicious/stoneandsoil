#pragma once
#include <filesystem>
#include <iostream>
#include <glad/glad.h>
#include <glm/fwd.hpp>

#include "i_bindable.hpp"
#include "../types.hpp"

namespace gfx {
    class Shader : public IBindable {
    public:
        struct Desc {
            std::filesystem::path path;
            u32 type;
        };

        template <typename... Descs>
        explicit Shader(Descs... shader_descs) : id{glCreateProgram()} {
            for (std::array shaders{compileShader(shader_descs)...}; const u32 shader : shaders) {
                glAttachShader(id, shader);
                glDeleteShader(shader);
            }

            glLinkProgram(id);

            i32 success{};
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if (!success) {
                std::array < char, 512 > error_buffer{};
                glGetProgramInfoLog(id, error_buffer.size(), nullptr, error_buffer.data());
                std::cerr << error_buffer.data() << std::endl;
            }

            Shader::bind();
        }

        ~Shader() override;

        void bind() const override;
        void unbind() const override;

        void setMat4(const std::string_view& name, const glm::mat4& value) const;
        void setI32(const std::string_view& name, i32 value) const;

    private:
        u32 id{};

        static u32 compileShader(Desc desc);
    };
} // gfx