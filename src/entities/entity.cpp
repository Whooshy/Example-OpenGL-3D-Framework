#include "entity.h"

Entity::Entity(Mesh* mesh) : mesh(mesh)
{
    scl = Vec3(1, 1, 1);
}

void Entity::draw(Renderer& renderer, ShaderProgram& shader)
{
    shader.transfer_mat4("transform_static", mat_transform(pos, rot, scl));
    renderer.draw_mesh(mesh);
}

void Entity::set_pos(Vec3 val)
{
    pos = val;
}

void Entity::set_rot(Vec3 val)
{
    rot = val;
}

void Entity::set_scl(Vec3 val)
{
    scl = val;
}