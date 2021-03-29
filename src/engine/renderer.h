#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "mesh.h"

extern long double engine_delta;

extern int engine_width, engine_height;

class Renderer
{
public:
    Renderer();

    void prepare();
    
    void draw_mesh(Mesh& mesh);
    void draw_mesh(Mesh* mesh);
};

#endif