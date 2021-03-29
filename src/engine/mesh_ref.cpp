#include "mesh_ref.h"

Mesh* refm_xquad;
Mesh* refm_yquad;
Mesh* refm_zquad;

void refm_loadmeshes()
{
    unsigned int indices[] = {0, 1, 2, 0, 3, 2};

    refm_xquad = new Mesh(1);

    refm_xquad->add_data(0, Vec3(0, 0, 0));
    refm_xquad->add_data(0, Vec3(0, 1, 0));
    refm_xquad->add_data(0, Vec3(0, 1, 1));
    refm_xquad->add_data(0, Vec3(0, 0, 1));

    refm_xquad->add_indices(indices, 6);
    refm_xquad->compile(true);

    refm_yquad = new Mesh(1);

    refm_yquad->add_data(0, Vec3(0, 0, 0));
    refm_yquad->add_data(0, Vec3(1, 0, 0));
    refm_yquad->add_data(0, Vec3(1, 0, 1));
    refm_yquad->add_data(0, Vec3(0, 0, 1));

    refm_yquad->add_indices(indices, 6);
    refm_yquad->compile(true);

    refm_zquad = new Mesh(1);

    refm_zquad->add_data(0, Vec3(0, 0, 0));
    refm_zquad->add_data(0, Vec3(1, 0, 0));
    refm_zquad->add_data(0, Vec3(1, 1, 0));
    refm_zquad->add_data(0, Vec3(0, 1, 0));

    refm_zquad->add_indices(indices, 6);
    refm_zquad->compile(true);
}

void refm_clearmeshes()
{
    delete refm_xquad;
    delete refm_yquad;
    delete refm_zquad;
}

Mesh* ref_xquad()
{
    return refm_xquad;
}

Mesh* ref_yquad()
{
    return refm_yquad;
}

Mesh* ref_zquad()
{
    return refm_zquad;
}