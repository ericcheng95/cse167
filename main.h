#ifndef _MAIN_H_
#define _MAIN_H_

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "shader.h"
#include <vector>
#include <list>
#include "Material.h"
#include "Model.h"
#include <iostream>

using namespace std;
using namespace glm;

#endif