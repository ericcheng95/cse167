#include "main.h"
#include "PrimaryWindow.h"
#include "ActionObject.h"

float lastFrameElapsedSeconds();

int main(void)
{
	PrimaryWindow::init(640, 480, "Primary Window");
	float secondsElapsed = 0.0000001f;
	while (!glfwWindowShouldClose(PrimaryWindow::window))
	{
		PrimaryWindow::display_callback();
		
		glfwPollEvents();
		
		ActionObject::allPerformActions(secondsElapsed);

		secondsElapsed = lastFrameElapsedSeconds();
	}

	// Destroy the window
	glfwDestroyWindow(PrimaryWindow::window);
	// Terminate GLFW
	glfwTerminate();

	exit(EXIT_SUCCESS);
}


void printFPS(long long duration)
{
	static long long totalDuration = 0;
	static long frames = 0;
	frames++;
	totalDuration += duration;
	if (totalDuration > 1000000000)
	{
		cout << "FPS: " << frames * 1000000000.0 / totalDuration << endl;
		frames = 0;
		totalDuration = 0;
	}
}

float lastFrameElapsedSeconds()
{
	static time_point<system_clock> lastTime = system_clock::now();
	auto thisTime = system_clock::now();
	long long duration = duration_cast<nanoseconds>(thisTime - lastTime).count();
	lastTime = thisTime;
	printFPS(duration);
	return (float)(duration / 1000000000.0);
}
