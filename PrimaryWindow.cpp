#include "PrimaryWindow.h"

GLFWwindow* PrimaryWindow::window;
int PrimaryWindow::width;
int PrimaryWindow::height;
mat4 PrimaryWindow::P;
mat4 PrimaryWindow::V;
unsigned int PrimaryWindow::shader;
unsigned int PrimaryWindow::selectionShader;
double PrimaryWindow::curX;
double PrimaryWindow::curY;
bool PrimaryWindow::leftPress;
bool PrimaryWindow::rightPress;
double PrimaryWindow::translateScale;

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
	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window,char_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetScrollCallback(window, scroll_callback);

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

	curX = 0;
	curY = 0;
	leftPress = false;
	rightPress = false;
	translateScale = 22.1 / height;

	shader = LoadShaders("shader.vert", "shader.frag");

	resize_callback(window, width, height);
}

void PrimaryWindow::display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glfwSwapBuffers(window);
	glfwPollEvents();
}

void PrimaryWindow::resize_callback(GLFWwindow* window, int width, int height)
{
}

void PrimaryWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void PrimaryWindow::char_callback(GLFWwindow* window, unsigned codepoint)
{
}

void PrimaryWindow::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
}

void PrimaryWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}

void PrimaryWindow::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}
