#include "PrimaryWindow.h"
#include "Light.h"


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

Skybox* PrimaryWindow::skybox;


vec3 PrimaryWindow::cam_pos(0.0f, 0.0f, 20.0f); // e  | Position of camera
vec3 PrimaryWindow::cam_look_at(0.0f, 0.0f, 0.0f); // d  | This is where the camera looks at
vec3 PrimaryWindow::cam_up(0.0f, 1.0f, 0.0f); // up | What orientation "up" is
vec3 PrimaryWindow::cam_right(1.0f, 0.0f, 0.0f); // up | What orientation "up" is


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

	skybox = new Skybox(width, height);


	//Initialize lights
	Light::directionalLights.push_back({ vec3(0, -1, -1), vec3(0.75, 0.75, 0.75), vec3(0.75, 0.75, 0.75), vec3(0.75, 0.75, 0.75) });
//	Light::pointLights.push_back({ vec3(0, 12, 0), vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), 0.02f });
//	Light::spotLights.push_back({ vec3(0, -1, 0), vec3(0, 12, 0), vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), 0.02f, 3.1415f / 72.0f ,64 });

	//Initialize objects
	Geode::scene->add(new Sphere());


	resize_callback(window, width, height);
}

void PrimaryWindow::display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox->draw(V);

	glUseProgram(shader);

	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &P[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &V[0][0]);
	glUniform3fv(glGetUniformLocation(shader, "cameraPos"), 1, &cam_pos[0]);

	Light::drawLights(shader);

	Geode::scene->draw(mat4(1.0f), shader);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void PrimaryWindow::resize_callback(GLFWwindow* window, int width, int height)
{
	PrimaryWindow::width = width;
	PrimaryWindow::height = height;

	skybox->updatePerspective(width, height);

	translateScale = 22.1 / height;
	glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
		V = lookAt(cam_pos, cam_look_at, cam_up);
	}
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
