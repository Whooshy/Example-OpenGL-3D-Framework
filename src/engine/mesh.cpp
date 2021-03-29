#include "mesh.h"

#include "../../lib/GL/glew.h"

Mesh::Mesh(unsigned int attribute_size) : attribute_size(attribute_size)
{
    glGenVertexArrays(1, &vao);
    data.resize(attribute_size);
    dimensions.resize(attribute_size);

    is_initialized = false;
}

void Mesh::create_attribute(unsigned int attribute, float* data, float data_size)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbos[attribute]);
    glBufferData(GL_ARRAY_BUFFER, data_size * sizeof(float), data, GL_STATIC_DRAW);
    glVertexAttribPointer(attribute, dimensions[attribute], GL_FLOAT, false, dimensions[attribute] * sizeof(float), 0);
    glEnableVertexAttribArray(attribute);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::add_data(unsigned int index, float x)
{
    data[index].push_back(x);

    dimensions[index] = 1;
}

void Mesh::add_data(unsigned int index, float x, float y)
{
    data[index].push_back(x);
    data[index].push_back(y);

    dimensions[index] = 2;
}

void Mesh::add_data(unsigned int index, float x, float y, float z)
{
    data[index].push_back(x);
    data[index].push_back(y);
    data[index].push_back(z);

    dimensions[index] = 3;
}

void Mesh::add_data(unsigned int index, Vec2 vec)
{
    data[index].push_back(vec.x);
    data[index].push_back(vec.y);

    dimensions[index] = 2;
}

void Mesh::add_data(unsigned int index, Vec3 vec)
{
    data[index].push_back(vec.x);
    data[index].push_back(vec.y);
    data[index].push_back(vec.z);

    dimensions[index] = 3;
}

void Mesh::add_data(unsigned int index, Vec4 vec)
{
    data[index].push_back(vec.x);
    data[index].push_back(vec.y);
    data[index].push_back(vec.z);
    data[index].push_back(vec.w);

    dimensions[index] = 4;
}

void Mesh::add_index(unsigned int index)
{
    indices.push_back(index);
}

void Mesh::add_indices(unsigned int* indices_array, unsigned int size)
{
    for(unsigned int i = 0; i < size; i++)
        indices.push_back(indices_array[i]);
}

void Mesh::bind()
{
    glBindVertexArray(vao);
}

void Mesh::compile(bool should_clear_data)
{
    bind();

    if(!is_initialized)
    {
        vbos.resize(attribute_size);
        for(unsigned int i = 0; i < attribute_size; i++)
        {
            glGenBuffers(1, &vbos[i]);
        }

        glGenBuffers(1, &ibo);
    }
    
    for(unsigned int i = 0; i < attribute_size; i++)
        create_attribute(i, data[i].data(), data[i].size());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    size = indices.size();

    if(should_clear_data)
    {
        for(unsigned int i = 0; i < attribute_size; i++)
        {
            std::vector<float>().swap(data[i]);
        }

        std::vector<std::vector<float> >().swap(data);
        std::vector<unsigned int>().swap(indices);

        std::vector<unsigned char>().swap(dimensions);

        data.resize(attribute_size);
        dimensions.resize(attribute_size);
    }

    glBindVertexArray(0);
    is_initialized = true;
}

unsigned int Mesh::get_data_usage()
{
    unsigned int data_size = 0;
    for(unsigned int i = 0; i < attribute_size; i++)
    {
        data_size += data[i].size() * sizeof(float);
    }
    data_size += indices.size() * sizeof(unsigned int);
    data_size += dimensions.size() * sizeof(unsigned char);
    return data_size;
}

std::vector<float> Mesh::get_data(unsigned int index)
{
    return data[index];
}

void Mesh::set_data(unsigned int index, float* data_new, unsigned int size, unsigned int dim)
{
    std::vector<float>().swap(data[index]);
    for(unsigned int i = 0; i < size; i++)
        data[index].push_back(data_new[i]);

    dimensions[index] = dim;
}