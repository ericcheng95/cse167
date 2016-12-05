#ifndef _pWINDOW_H_
#define _pWINDOW_H_
#include "main.h"
#include "Geode.h"
#include "Sphere.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Pyramid.h"
#include "skybox.h"
#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "shader.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <random>


class PrimaryWindow
{
public:
	static GLFWwindow* window;
	static int width;
	static int height;
	static unsigned int shader, dGeometryShader, dLightingShader, dSSAOShader, dSSAOBlurShader;
	static unsigned int selectionShader;

	static GLuint gBuffer;
	static GLuint gPositionDepth, gNormal, gAlbedo;


	static GLuint ssaoFBO, ssaoBlurFBO, noiseTexture;
	static default_random_engine generator;
	static vector<glm::vec3> ssaoKernel;
	static vector<glm::vec3> ssaoNoise;

	static bool enableCulling;

	static Skybox* skybox;

	static void init(int width, int height, char* title);
	static void display_callback();
	static void resize_callback(GLFWwindow* window, int width, int height);

	//From LearnOpenGL: http://www.learnopengl.com/code_viewer.php?code=advanced-lighting/bloom
	//Call opengl to render from texture sampler2D/samplerCube
	static void RenderQuad();
	static void RenderCube();
private:
	static void genGBuffer();
};

#endif
