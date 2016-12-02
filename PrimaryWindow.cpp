#include "PrimaryWindow.h"
#include "Light.h"
#include "camera.h"
#include "control.h"


GLFWwindow* PrimaryWindow::window;
int PrimaryWindow::width;
int PrimaryWindow::height;
unsigned int PrimaryWindow::shader;
unsigned int PrimaryWindow::selectionShader;
unsigned int PrimaryWindow::gBuffer;

Skybox* PrimaryWindow::skybox;

bool PrimaryWindow::enableCulling = true;

void PrimaryWindow::init(int width, int height, char* title)
{
	PrimaryWindow::width = width;
	PrimaryWindow::height = height;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return;
	}
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));
#ifdef GL_SHADING_LANGUAGE_VERSION
	printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif

	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwGetFramebufferSize(window, &width, &height);

	glfwSetFramebufferSizeCallback(window, resize_callback);

#ifndef __APPLE__
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		glfwTerminate();
	}
	fprintf(stdout, "Current GLEW version: %s\n", glewGetString(GLEW_VERSION));
#endif
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0, 0, 0, 1.0f);


	//Initialize stuff
	genGBuffer();
	shader = LoadShaders("shader.vert", "shader.frag");
	skybox = new Skybox(width, height);
	Control::init(window);
	Geode::init(shader);
	Camera::init(shader);
	Light::init();

	
	//Initialize objects
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			Cube* p = new Cube();
			p->translate(i - 50.0f, -10.0f, j - 50.0f);
			Geode::scene->add(p);
		}
	}

	
	
	resize_callback(window, width, height);
}

void PrimaryWindow::display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera::enable();

	skybox->draw(Camera::V);

	glUseProgram(shader);

	Light::drawLights(shader);

	Geode::scene->draw(mat4(1.0f), shader);

	glfwSwapBuffers(window);
}

void PrimaryWindow::resize_callback(GLFWwindow* window, int width, int height)
{
	PrimaryWindow::width = width;
	PrimaryWindow::height = height;

	skybox->updatePerspective(width, height);

	glViewport(0, 0, width, height);

	if (height > 0)
	{
		Camera::updateP();
		Camera::updateV();
	}
}

void PrimaryWindow::genGBuffer()
{
//	glGenFramebuffers(1, &gBuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//	GLuint gPosition, gNormal, gAlbedoSpec;
//	// - Position color buffer
//	glGenTextures(1, &gPosition);
//	glBindTexture(GL_TEXTURE_2D, gPosition);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
//	// - Normal color buffer
//	glGenTextures(1, &gNormal);
//	glBindTexture(GL_TEXTURE_2D, gNormal);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
//	// - Color + Specular color buffer
//	glGenTextures(1, &gAlbedoSpec);
//	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
//	// - Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
//	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
//	glDrawBuffers(3, attachments);
}
