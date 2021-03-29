#ifndef _MESH_REF_H_
#define _MESH_REF_H_

#include "mesh.h"

void refm_loadmeshes();
void refm_clearmeshes();

Mesh* ref_xquad();
Mesh* ref_yquad();
Mesh* ref_zquad();

#endif
