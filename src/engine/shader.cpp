#include "shader.h"

#include "../../lib/GL/glew.h"

#include <fstream>
#include <iostream>

Shader::Shader(const char* filepath, unsigned int type) : filepath(filepath), type(type)
{
    shader = glCreateShader(type);

    std::string source = get_source();
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int status;
    char log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(!status)
    {
        glGetShaderInfoLog(shader, 512, NULL, log);
        std::cout << log << std::endl;
    }
}

std::string Shader::get_source()
{
    std::ifstream reader(filepath);
    std::string line, output;

    if(reader.good())
    {
        while(std::getline(reader, line))
        {
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Cannot locate or open file: " << filepath << std::endl;
    }

    const char* src = output.c_str();
    return src;
}

ShaderProgram::ShaderProgram()
{
    program = glCreateProgram();
}

void ShaderProgram::add_shader(Shader shader)
{
    glAttachShader(program, shader.get());
}

void ShaderProgram::build()
{
    glLinkProgram(program);

    int status;
    char log[512];

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(!status)
    {
        glGetShaderInfoLog(program, 512, NULL, log);
        std::cout << log << std::endl;
    }

    glValidateProgram(program);

    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
    if(!status)
    {
        glGetShaderInfoLog(program, 512, NULL, log);
        std::cout << log << std::endl;
    }
}

void ShaderProgram::transfer_int(const char* name, int val)
{
    glUniform1i(glGetUniformLocation(program, name), val);
}

void ShaderProgram::transfer_vec3(const char* name, Vec3 vec)
{
    glUniform3f(glGetUniformLocation(program, name), vec.x, vec.y, vec.z);
}

void ShaderProgram::transfer_vec4(const char* name, Vec4 vec)
{
    glUniform4f(glGetUniformLocation(program, name), vec.x, vec.y, vec.z, vec.w);
}

void ShaderProgram::transfer_mat4(const char* name, Mat4x4 mat)
{
    float array[16];
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, false, mat.get_readable_array(array));
}

void ShaderProgram::use()
{
    glUseProgram(program);
}