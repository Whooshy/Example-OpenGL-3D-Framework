#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "../engine/mesh.h"
#include "../engine/renderer.h"
#include "../engine/shader.h"

class Entity
{
public:
    Entity(Mesh* mesh);

    Vec3 get_pos() const { return pos; }
    Vec3 get_rot() const { return rot; }
    Vec3 get_scl() const { return scl; }

    void set_pos(Vec3 val);
    void set_rot(Vec3 val);
    void set_scl(Vec3 val);

    void draw(Renderer& renderer, ShaderProgram& shader);
private:
    Mesh* mesh;
    Vec3 pos, rot, scl;
};

#endif