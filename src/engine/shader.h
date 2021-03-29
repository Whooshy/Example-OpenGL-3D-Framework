#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>

#include "../utils/utilmath.h"

class Shader
{
public:
    Shader(const char* filepath, unsigned int type);

    unsigned int get() const { return shader; };
private:
    const char* filepath;
    unsigned int type, shader;

    std::string get_source();
};

class ShaderProgram
{
public:
    ShaderProgram();

    void add_shader(Shader shader);
    void build();

    void use();

    void transfer_int(const char* name, int val);

    void transfer_vec3(const char* name, Vec3 vec);
    void transfer_vec4(const char* name, Vec4 vec);
    
    void transfer_mat4(const char* name, Mat4x4 mat);
private:
    unsigned int program;
};

#endif