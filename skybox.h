#pragma once
#include "main.h"
#include "shader.h"
#include "image.h"
#include "texture.h"

class Skybox
{
public:

	Skybox(int width, int height);
	void draw(mat4 view);
	void updatePerspective(int width, int height);
private:
	unsigned int skyboxShader;
	mat4 skyboxPerspective;

	GLuint VAO, VBO;
	Texture* texture;

};
