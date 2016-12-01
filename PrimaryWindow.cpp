#include "PrimaryWindow.h"
#include "Light.h"
#include "camera.h"


GLFWwindow* PrimaryWindow::window;
int PrimaryWindow::width;
int PrimaryWindow::height;
unsigned int PrimaryWindow::shader;
unsigned int PrimaryWindow::selectionShader;
double PrimaryWindow::curX;
double PrimaryWindow::curY;
bool PrimaryWindow::leftPress;
bool PrimaryWindow::rightPress;
double PrimaryWindow::translateScale;

Skybox* PrimaryWindow::skybox;

bool PrimaryWindow::enableCulling = false;

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

	Geode::scene->enableCulling = false;
	//Initialize objects



	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			Cube* p = new Cube();
			p->translate(i - 50, -10, j - 50);
			//Geode::scene->add(p);
		}
	}

	
	
	resize_callback(window, width, height);


	Camera::uProjection = glGetUniformLocation(shader, "projection");
	Camera::uView = glGetUniformLocation(shader, "view");
	Camera::uCamera = glGetUniformLocation(shader, "cameraPos");

	Geode::uModel = glGetUniformLocation(shader, "model");
	Geode::uDiffuse = glGetUniformLocation(shader, "material.diffuseCoeff");
	Geode::uSpecular = glGetUniformLocation(shader, "material.specularCoeff");
	Geode::uAmbient = glGetUniformLocation(shader, "material.ambientCoeff");
	Geode::uShininess = glGetUniformLocation(shader, "material.shininessExp");
	Geode::uReflectivity = glGetUniformLocation(shader, "material.reflectivity");
}

void PrimaryWindow::display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox->draw(Camera::V);

	glUseProgram(shader);


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
		Camera::updateP();
		Camera::updateV();
	}
}

void PrimaryWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void PrimaryWindow::char_callback(GLFWwindow* window, unsigned codepoint)
{
	switch (codepoint)
	{
	case 'r':
		Camera::reset();
		break;
	case 'c':
		enableCulling = !enableCulling;
		break;
	}
}

void PrimaryWindow::cursor_pos_callback(GLFWwindow* window, double newX, double newY)
{
	if (leftPress)
	{
		mat4 rotation = Camera::trackballRotate(Camera::trackballMap(curX, curY), Camera::trackballMap(newX, newY));
		Camera::cam_pos = vec3(rotation * vec4(Camera::cam_pos, 1.0));
		Camera::updateV();
	}
	curX = newX;
	curY = newY;
}

void PrimaryWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		rightPress = action == GLFW_PRESS;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		leftPress = action == GLFW_PRESS;
	}
}

void PrimaryWindow::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (length(Camera::cam_pos) < 10000.0f || yoffset > 0)
	{
		Camera::cam_pos *= 1 + yoffset / -10.0f;
		Camera::updateV();
	}
}


