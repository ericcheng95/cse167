#pragma once
#include "main.h"
#include "camera.h"

class Control
{
public:
	static void init(GLFWwindow* window);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void char_callback(GLFWwindow* window, unsigned int codepoint);
	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
private:
	static double curMouseX;
	static double curMouseY;
	static bool leftClick, rightClick;
	static bool leftPress, rightPress, upPress, downPress;
	static bool wPress, aPress, sPress, dPress;
};
