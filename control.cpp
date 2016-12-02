#include "control.h"
#include "PrimaryWindow.h"

double Control::curMouseX = 0;
double Control::curMouseY = 0;
bool Control::leftClick = false, Control::rightClick = false;
bool Control::leftPress = false, Control::rightPress = false, Control::upPress = false, Control::downPress = false;
bool Control::wPress = false, Control::aPress = false, Control::sPress = false, Control::dPress = false;

void Control::init(GLFWwindow* window)
{
	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window, char_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

void Control::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_UP:
			upPress = true;
			break;
		case GLFW_KEY_DOWN:
			downPress = true;
			break;
		case GLFW_KEY_LEFT:
			leftPress = true;
			break;
		case GLFW_KEY_RIGHT:
			rightPress = true;
			break;
		case GLFW_KEY_W:
			wPress = true;
			break;
		case GLFW_KEY_S:
			sPress = true;
			break;
		case GLFW_KEY_A:
			aPress = true;
			break;
		case GLFW_KEY_D:
			dPress = true;
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case GLFW_KEY_UP:
			upPress = false;
			break;
		case GLFW_KEY_DOWN:
			downPress = false;
			break;
		case GLFW_KEY_LEFT:
			leftPress = false;
			break;
		case GLFW_KEY_RIGHT:
			rightPress = false;
			break;
		case GLFW_KEY_W:
			wPress = false;
			break;
		case GLFW_KEY_S:
			sPress = false;
			break;
		case GLFW_KEY_A:
			aPress = false;
			break;
		case GLFW_KEY_D:
			dPress = false;
			break;
		}
	}
}

void Control::char_callback(GLFWwindow* window, unsigned codepoint)
{
	switch (codepoint)
	{
	case 'r':
		Camera::reset();
		break;
	case 'c':
		PrimaryWindow::enableCulling = !PrimaryWindow::enableCulling;
		break;
	}
}

void Control::cursor_pos_callback(GLFWwindow* window, double newX, double newY)
{
	if (leftClick)
	{
		mat4 rotation = Camera::trackballRotate(Camera::trackballMap(curMouseX, curMouseY), Camera::trackballMap(newX, newY));
		Camera::cam_pos = vec3(rotation * vec4(Camera::cam_pos, 1.0));
		Camera::updateV();
	}
	curMouseX = newX;
	curMouseY = newY;
}

void Control::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		rightClick = action == GLFW_PRESS;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		leftClick = action == GLFW_PRESS;
	}
}

void Control::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (length(Camera::cam_pos) < 10000.0f || yoffset > 0)
	{
		Camera::cam_pos *= 1 + yoffset / -10.0f;
		Camera::updateV();
	}
}
