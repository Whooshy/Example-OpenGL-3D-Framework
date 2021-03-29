#include "viewport.h"

#include <cmath>
#include <iostream>

#include "renderer.h"

Vec3 pos, target;

float cur_y = 0;
float del_y = 0;
float pre_y = 0;

Vec3 getviewport_pos()
{
    return pos;
}

Vec3 getviewport_target()
{
    return target;
}

void setviewport_pos(Vec3 val)
{
    pos = val;
}

void setviewport_target(Vec3 val)
{
    target = val;
}

void updateviewport_pos(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_W))
    {
        pos -= target * (engine_delta * 10);
    }
    if(glfwGetKey(window, GLFW_KEY_S))
    {
        pos += target * (engine_delta * 10);
    }
    if(glfwGetKey(window, GLFW_KEY_A))
    {
        pos -= normalize(cross(target, Vec3(0, 1, 0))) * (engine_delta * 10);
    }
    if(glfwGetKey(window, GLFW_KEY_D))
    {
        pos += normalize(cross(target, Vec3(0, 1, 0))) * (engine_delta * 10);
    }
}

void updateviewport_target(double x, double y, double sensitivity)
{
    x *= sensitivity;
    y *= sensitivity;
    del_y = y - pre_y;

    if(cur_y <= 0.1)
    {
        cur_y = 0.1;
        if(del_y > 0)
        {
            cur_y += del_y;
        }
    }
    else if(cur_y >= 3.04)
    {
        cur_y = 3.04;
        if(del_y < 0)
        {
            cur_y += del_y;
        }
    }
    else
    {
        cur_y += del_y;
    }

    target.x = std::sin(x);
    target.y = std::tan(cur_y - (3.1416 / 2));
    target.z = std::cos(x);

    target = normalize(target);
    pre_y = y;
}