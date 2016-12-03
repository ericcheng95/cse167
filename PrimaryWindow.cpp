#include "PrimaryWindow.h"
#include "Light.h"
#include "camera.h"
#include "control.h"


GLFWwindow* PrimaryWindow::window;
int PrimaryWindow::width;
int PrimaryWindow::height;
unsigned int PrimaryWindow::shader;
unsigned int PrimaryWindow::selectionShader, PrimaryWindow::dGeometryShader, PrimaryWindow::dLightingShader;
unsigned int PrimaryWindow::gBuffer;

Skybox* PrimaryWindow::skybox;

bool PrimaryWindow::enableCulling = true;

void PrimaryWindow::init(int width, int height, char* title)
{
	PrimaryWindow::width = width;
	PrimaryWindow::height = height;

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


	//Load shader and shader defaults
	shader = LoadShaders("shader.vert", "shader.frag");
	dGeometryShader = LoadShaders("dGeometry.vert", "dGeometry.frag");
	dLightingShader = LoadShaders("dLighting.vert", "dLighting.frag");
	glUniform1i(glGetUniformLocation(dLightingShader, "gPosition"), 0);
	glUniform1i(glGetUniformLocation(dLightingShader, "gNormal"), 1);
	glUniform1i(glGetUniformLocation(dLightingShader, "gAlbedoSpec"), 2);
	genGBuffer();

	//Initialize stuff
	skybox = new Skybox(width, height);
	Control::init(window);
	Geode::init(shader);
	Camera::init();
	Light::init();

	
	//Initialize objects
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			Cube* p = new Cube();
			p->translate(i - 50.0f, -10.0f, j - 50.0f);
			Geode::scene->add(p);
		}
	}

	
	
	resize_callback(window, width, height);
}

void PrimaryWindow::display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera::enable(shader);

	skybox->draw(Camera::V);

	glUseProgram(shader);

	Light::drawLights(shader);

	Geode::scene->draw(mat4(1.0f), shader);


	glfwSwapBuffers(window);


	 

//	// 1. Geometry Pass: render scene's geometry/color data into gbuffer
//	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	Camera::enable(dGeometryShader);
//	shaderGeometryPass.Use();
//	for (GLuint i = 0; i < objectPositions.size(); i++)
//	{
//		model = mat4();
//		model = translate(model, objectPositions[i]);
//		model = scale(model, glm::vec3(0.25f));
//		glUniformMatrix4fv(glGetUniformLocation(shaderGeometryPass.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//		cyborg.Draw(shaderGeometryPass);
//	}
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
// // 2. Lighting Pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	shaderLightingPass.Use();
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, gPosition);
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, gNormal);
//	glActiveTexture(GL_TEXTURE2);
//	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
//	Camera::enable(dLightingShader);
//	// Also send light relevant uniforms
//	for (GLuint i = 0; i < lightPositions.size(); i++)
//	{
//		glUniform3fv(glGetUniformLocation(shaderLightingPass.Program, ("lights[" + std::to_string(i) + "].Position").c_str()), 1, &lightPositions[i][0]);
//		glUniform3fv(glGetUniformLocation(shaderLightingPass.Program, ("lights[" + std::to_string(i) + "].Color").c_str()), 1, &lightColors[i][0]);
//		// Update attenuation parameters and calculate radius
//		const GLfloat constant = 1.0; // Note that we don't send this to the shader, we assume it is always 1.0 (in our case)
//		const GLfloat linear = 0.7;
//		const GLfloat quadratic = 1.8;
//		glUniform1f(glGetUniformLocation(shaderLightingPass.Program, ("lights[" + std::to_string(i) + "].Linear").c_str()), linear);
//		glUniform1f(glGetUniformLocation(shaderLightingPass.Program, ("lights[" + std::to_string(i) + "].Quadratic").c_str()), quadratic);
//	}
//	// Finally render quad
//	RenderQuad();

}

void PrimaryWindow::resize_callback(GLFWwindow* window, int width, int height)
{
	PrimaryWindow::width = width;
	PrimaryWindow::height = height;

	skybox->updatePerspective(width, height);

	glViewport(0, 0, width, height);

	if (height > 0)
	{
		Camera::updateP();
		Camera::updateV();
	}
}

void PrimaryWindow::genGBuffer()
{
	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	GLuint gPosition, gNormal, gAlbedoSpec;
	// - Position color buffer
	glGenTextures(1, &gPosition);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
	// - Normal color buffer
	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
	// - Color + Specular color buffer
	glGenTextures(1, &gAlbedoSpec);
	glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedoSpec, 0);
	// - Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);
	// - Create and attach depth buffer (renderbuffer)
	GLuint rboDepth;
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	// - Finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "Framebuffer not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
