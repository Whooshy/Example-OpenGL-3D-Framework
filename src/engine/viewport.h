#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "../../lib/GLFW/glfw3.h"

#include "../utils/utilmath.h"

Vec3 getviewport_pos();
Vec3 getviewport_target();

void setviewport_pos(Vec3 val);
void setviewport_target(Vec3 val);

void updateviewport_pos(GLFWwindow* window);
void updateviewport_target(double x, double y, double sensitivity);

#endif