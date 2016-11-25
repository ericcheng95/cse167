#include "main.h"
#include "PrimaryWindow.h"


int main(void)
{
	chrono::time_point<chrono::system_clock> time_point = chrono::system_clock::now();
	long frames = 0;
	
	PrimaryWindow::init(640, 480, "Primary Window");
	
	while (!glfwWindowShouldClose(PrimaryWindow::window))
	{
	
		PrimaryWindow::display_callback();


		frames++;
		long long t = chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - time_point).count();
		if (t > 1000000000) {
			cout <<"FPS: " << frames * 1000000000.0 / t << endl;
			frames = 0;
			time_point = chrono::system_clock::now();
		}
	}

	// Destroy the window
	glfwDestroyWindow(PrimaryWindow::window);
	// Terminate GLFW
	glfwTerminate();

	exit(EXIT_SUCCESS);
}
