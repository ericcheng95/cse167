#include "main.h"
#include "PrimaryWindow.h"


int main(void)
{
	chrono::time_point<chrono::system_clock> time_point = chrono::system_clock::now();
	double frames = 0;
	while (!glfwWindowShouldClose(PrimaryWindow::window))
	{
	
		PrimaryWindow::display_callback();


		frames++;
		long long t = chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - time_point).count();
		if (t > 1000000000.0) {
			cout << "FPS: " << frames / t << endl;
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
