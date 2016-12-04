#include "main.h"
#include "PrimaryWindow.h"
#include <stdio.h>
#include "include/irrKlang.h"
#include <conio.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

float lastFrameElapsedSeconds();
void error_callback(int error, const char* description);

int main(void)
{
	ISoundEngine* engine = createIrrKlangDevice();
	ISoundSource* bgm = engine->addSoundSourceFromFile("getout.ogg");

	engine->play2D(bgm, true);

	glfwSetErrorCallback(error_callback);

	PrimaryWindow::init(640, 480, "Primary Window");
	float secondsElapsed = 0.0000001f;

	while (!glfwWindowShouldClose(PrimaryWindow::window))
	{

		PrimaryWindow::display_callback();
		
		glfwPollEvents();

		secondsElapsed = lastFrameElapsedSeconds();
	}


	engine->drop(); // delete engine

	// Destroy the window
	glfwDestroyWindow(PrimaryWindow::window);
	// Terminate GLFW
	glfwTerminate();


	exit(EXIT_SUCCESS);
}


void printFPS(float duration)
{
	static float totalDuration = 0;
	static int frames = 0;
	frames++;
	totalDuration += duration;
	if (totalDuration > 1.0f)
	{
		cout << "FPS: " << frames / totalDuration << endl;
		frames = 0;
		totalDuration = 0;
	}
}

float lastFrameElapsedSeconds()
{
	static float lastTime = glfwGetTime();
	auto thisTime = glfwGetTime();
	float duration = thisTime - lastTime;
	lastTime = thisTime;
	printFPS(duration);
	return duration;
}

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}


void soundInit(ISoundEngine* engine)
{
	
}