#include <cmath>
#include <iostream>

#include "../lib/GL/glew.h"
#include "../lib/GLFW/glfw3.h"

#include "engine/mesh.h"
#include "engine/mesh_ref.h"
#include "engine/renderer.h"
#include "engine/shader.h"
#include "engine/viewport.h"

#include "entities/entity.h"

#include "utils/font.h"
#include "utils/texture.h"
#include "utils/ui.h"

long double engine_delta;
int engine_width, engine_height;

bool enable_mouse;

void callback_cursor(GLFWwindow* window, double x, double y);
void callback_resize(GLFWwindow* window, int width, int height);

const char* check_glerror()
{
    int err = glGetError();
    switch(err)
    {
        case GL_NO_ERROR:
            return "No OpenGL errors.";
            break;
        case GL_INVALID_ENUM:
            return "OpenGL Error: INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            return "OpenGL Error: INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            return "OpenGL Error: INVALID_OPERATION";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "OpenGL Error: INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            return "OpenGL Error: OUT_OF_MEMORY";
            break;
        case GL_STACK_UNDERFLOW:
            return "OpenGL Error: STACK_UNDERFLOW";
            break;
        case GL_STACK_OVERFLOW:
            return "OpenGL Error: STACK_OVERFLOW";
            break;
    }

    return "Unknown OpenGL error!";
}

int main()
{
    engine_delta = 0.1667f;

    engine_width = 1280;
    engine_height = 720;

    enable_mouse = false;

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Game", NULL, NULL);

    glfwSetCursorPosCallback(window, callback_cursor);
    glfwSetFramebufferSizeCallback(window, callback_resize);

    glfwMakeContextCurrent(window);
    glewInit();

    Renderer renderer;

    Shader s_main_vert("../res/shaders/main.vert", GL_VERTEX_SHADER);
    Shader s_main_frag("../res/shaders/main.frag", GL_FRAGMENT_SHADER);

    ShaderProgram s_main;

    s_main.add_shader(s_main_vert);
    s_main.add_shader(s_main_frag);

    s_main.build();

    Shader s_ui_vert("../res/shaders/ui.vert", GL_VERTEX_SHADER);
    Shader s_ui_frag("../res/shaders/ui.frag", GL_FRAGMENT_SHADER);

    ShaderProgram s_ui;

    s_ui.add_shader(s_ui_vert);
    s_ui.add_shader(s_ui_frag);

    s_ui.build();

    refm_loadmeshes();

    Mesh* test = ref_zquad();
    Entity test_ent(test);

    test_ent.set_pos(Vec3(-0.5f, -0.5f, -2));

    Font font("../res/textures/font.ofk");
    Texture font_tex("../res/textures/font.bmp", true, false);

    UIText debug(Vec2(-engine_width / 2 + 5, engine_height / 2 - 20), 0.6f, false, "[EMPTY]", &font);

    glfwSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    double timer = glfwGetTime();

    int fps = 0;

    while(!glfwWindowShouldClose(window))
    {
        engine_delta = glfwGetTime() - timer;
        timer = glfwGetTime();

        fps = std::round(1 / engine_delta);

        renderer.prepare();

        glEnable(GL_DEPTH_TEST);

        s_main.use();
        s_main.transfer_mat4("projection", mat_perspective(70.f, (float) engine_width / (float) engine_height, 0.05f, 1000.f));
        s_main.transfer_mat4("viewport", mat_view(getviewport_pos(), getviewport_pos() + getviewport_target(), Vec3(0, 1, 0)));
        s_main.transfer_int("draw_mode", 0);

        test_ent.draw(renderer, s_main);

        glDisable(GL_DEPTH_TEST);

        s_ui.use();
        s_ui.transfer_mat4("projection", mat_ortho(0, engine_width, 0, engine_height, -1, 1));
        font_tex.bind();

        debug.set_pos(Vec2(-engine_width / 2 + 5, engine_height / 2 - 20));
        debug.draw(renderer, s_ui);

        std::string debug_text = "CGJ Framework. FPS: " + std::to_string(fps) + ", (delta: " + std::to_string(engine_delta) + ")\n";
        debug_text += check_glerror();
        debug_text += "\n\nViewport: POS (" + std::to_string(getviewport_pos().x) + ", " + std::to_string(getviewport_pos().y) + ", " + std::to_string(getviewport_pos().z) + ")";

        if(debug.get_message() != debug_text)
        {
            debug.build(debug_text);
        }

        updateviewport_pos(window);

        if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1))
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            enable_mouse = true;
        }
        if(glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            enable_mouse = false;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    refm_clearmeshes();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void callback_cursor(GLFWwindow* window, double x, double y)
{
    if(enable_mouse) updateviewport_target(x, y, 0.01f);
}

void callback_resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    engine_width = width;
    engine_height = height;
}