#include "Includes"

Window Window::a(640, 480, "a");
Window Window::b(640, 480, "b");

Window::Window(int width, int height, char* title): width(width), height(height)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfw = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!glfw)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(glfw);
	glfwSwapInterval(1);
	glfwGetFramebufferSize(glfw, &width, &height);
	glfwSetFramebufferSizeCallback(glfw, resize);


	resize(glfw, width, height);
}

void Window::resize(GLFWwindow* window, int w, int h)
{
	width = w;
	height = h;
	onResize();
}
