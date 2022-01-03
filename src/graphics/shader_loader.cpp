#include "shader_loader.h"

namespace trade_history
{
    shader_loader &shader_loader::instance = shader_loader::create();

    shader_loader::shader_loader() : current_index(0)
    {}

    void shader_loader::load(const char *vert_file, const char *frag_file)
    {
        std::string vertexCode;
        std::string fragmentCode;

        std::ifstream vShaderFile{};
        std::ifstream fShaderFile{};

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            vShaderFile.open(vert_file);
            fShaderFile.open(frag_file);

            std::stringstream vShaderStream, fShaderStream;

            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // close file handlers
            vShaderFile.close();
            fShaderFile.close();

            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure &e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << e.what() << std::endl;
        }

        const char *vertex_src = vertexCode.c_str();
        const char *fragment_src = fragmentCode.c_str();

        GLuint vertex_shader;
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_src, nullptr);
        glCompileShader(vertex_shader);

        if (!_is_successful(vertex_shader, GL_COMPILE_STATUS)) return;

        GLuint fragment_shader;
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_src, nullptr);
        glCompileShader(fragment_shader);

        if (!_is_successful(fragment_shader, GL_COMPILE_STATUS)) return;

        program_ids[current_index] = glCreateProgram();
        glAttachShader(program_ids[current_index], vertex_shader);
        glAttachShader(program_ids[current_index], fragment_shader);
        glLinkProgram(program_ids[current_index]);

        if (!_is_successful(program_ids[current_index], GL_LINK_STATUS)) return;

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        current_index++;
    }

    void shader_loader::use(unsigned short program_id_index)
    {
        shader_to_use = program_ids[program_id_index];
        glUseProgram(shader_to_use);
    }

    void shader_loader::set_int(const char *name, int value)
    {
        glUniform1i(glGetUniformLocation(shader_to_use, name), value);
    }

    void shader_loader::set_mat4(const char *name, float *value)
    {
        glUniformMatrix4fv(glGetUniformLocation(shader_to_use, name), 1, GL_FALSE, value);
    }

    void shader_loader::set_vec3(const char *name, float *value)
    {
        glUniform3fv(glGetUniformLocation(shader_to_use, name), 1, value);
    }

    bool shader_loader::_is_successful(GLuint id, GLuint action)
    {
        int success;
        char infoLog[512];
        if (action == GL_COMPILE_STATUS)
        {
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(id, 512, NULL, infoLog);
                std::cerr << "Shader Compilation Error: " << infoLog;
            }
        }
        else if (action == GL_LINK_STATUS)
        {
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(id, 512, NULL, infoLog);
                std::cerr << "Shader Linking Error: " << infoLog;
            }
        }

        return success;
    }

}