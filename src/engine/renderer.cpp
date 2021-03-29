#include "renderer.h"

#include "../../lib/GL/glew.h"

Renderer::Renderer()
{

}

void Renderer::prepare()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw_mesh(Mesh& mesh)
{
    mesh.bind();
    glDrawElements(GL_TRIANGLES, mesh.size, GL_UNSIGNED_INT, 0);
}

void Renderer::draw_mesh(Mesh* mesh)
{
    mesh->bind();
    glDrawElements(GL_TRIANGLES, mesh->size, GL_UNSIGNED_INT, 0);
}