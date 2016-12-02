#include "PrimaryWindow.h"
#include "Light.h"
#include "camera.h"
#include "control.h"


GLFWwindow* PrimaryWindow::window;
int PrimaryWindow::width;
int PrimaryWindow::height;
unsigned int PrimaryWindow::shader;
unsigned int PrimaryWindow::selectionShader;

Skybox* PrimaryWindow::skybox;

bool PrimaryWindow::enableCulling = true;

void PrimaryWindow::init(int width, int height, char* title)
{
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
