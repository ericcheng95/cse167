#ifndef _sWINDOW_H_
#define _sWINDOW_H_
#include "Geode.h"

class SecondaryWindow
{
public:
	static GLFWwindow* window;
	static int width;
	static int height;

	static void init(int width, int height, char* title);
	static void display_callback();
};

#endif
