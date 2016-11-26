#ifndef _pWINDOW_H_
#define _pWINDOW_H_
#include "Geode.h"
#include "Sphere.h"
#include "Cube.h"
#include "Cylinder.h"
#include "Pyramid.h"

class PrimaryWindow
{
public:
	static GLFWwindow* window;
	static int width;
	static int height;
	static mat4 P;
	static mat4 V;
	static unsigned int shader;
	static unsigned int selectionShader;

	static vec3 cam_pos, cam_look_at, cam_up, cam_right;


	static void init(int width, int height, char* title);
	static void display_callback();
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void char_callback(GLFWwindow* window, unsigned int codepoint);
	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
	static double curX;
	static double curY;
	static bool leftPress;
	static bool rightPress;
	static double translateScale;
};

#endif
