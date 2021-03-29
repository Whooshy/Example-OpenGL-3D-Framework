#ifndef _MESH_H_
#define _MESH_H_

#include <vector>

#include "../utils/utilmath.h"

class Mesh
{
public:
    Mesh(unsigned int attribute_size);

    void add_data(unsigned int index, float x);
    void add_data(unsigned int index, float x, float y);
    void add_data(unsigned int index, float x, float y, float z);

    void add_data(unsigned int index, Vec2 vec);
    void add_data(unsigned int index, Vec3 vec);
    void add_data(unsigned int index, Vec4 vec);

    std::vector<float> get_data(unsigned int index);
    void set_data(unsigned int index, float* data_new, unsigned int size, unsigned int dim);

    void add_index(unsigned int index);
    void add_indices(unsigned int* indices_array, unsigned int size);

    void compile(bool should_clear_data);
    void destroy();

    void bind();

    unsigned int get_data_usage();

    unsigned int size;
private:
    void create_attribute(unsigned int attribute, float* data, float data_size);
    unsigned int attribute_size, vao;
    bool is_initialized;

    std::vector<std::vector<float> > data;
    std::vector<unsigned int> indices; 

    std::vector<unsigned char> dimensions;

    std::vector<unsigned int> vbos;
    unsigned int ibo;
};

#endif