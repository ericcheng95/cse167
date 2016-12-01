#include "skybox.h"

Skybox::Skybox(int width, int height)
{
	skyboxShader = LoadShaders("skyboxShader.vert", "skyboxShader.frag");

	updatePerspective(width, height);

	texture = new Texture(GL_TEXTURE_CUBE_MAP, "Image");
	GLfloat skyboxVertices[] = {
		// Positions          
		-300001.0f, 300001.0f, -300001.0f,
		-300001.0f, -300001.0f, -300001.0f,
		300001.0f, -300001.0f, -300001.0f,
		300001.0f, -300001.0f, -300001.0f,
		300001.0f, 300001.0f, -300001.0f,
		-300001.0f, 300001.0f, -300001.0f,

		-300001.0f, -300001.0f, 300001.0f,
		-300001.0f, -300001.0f, -300001.0f,
		-300001.0f, 300001.0f, -300001.0f,
		-300001.0f, 300001.0f, -300001.0f,
		-300001.0f, 300001.0f, 300001.0f,
		-300001.0f, -300001.0f, 300001.0f,

		300001.0f, -300001.0f, -300001.0f,
		300001.0f, -300001.0f, 300001.0f,
		300001.0f, 300001.0f, 300001.0f,
		300001.0f, 300001.0f, 300001.0f,
		300001.0f, 300001.0f, -300001.0f,
		300001.0f, -300001.0f, -300001.0f,

		-300001.0f, -300001.0f, 300001.0f,
		-300001.0f, 300001.0f, 300001.0f,
		300001.0f, 300001.0f, 300001.0f,
		300001.0f, 300001.0f, 300001.0f,
		300001.0f, -300001.0f, 300001.0f,
		-300001.0f, -300001.0f, 300001.0f,

		-300001.0f, 300001.0f, -300001.0f,
		300001.0f, 300001.0f, -300001.0f,
		300001.0f, 300001.0f, 300001.0f,
		300001.0f, 300001.0f, 300001.0f,
		-300001.0f, 300001.0f, 300001.0f,
		-300001.0f, 300001.0f, -300001.0f,

		-300001.0f, -300001.0f, -300001.0f,
		-300001.0f, -300001.0f, 300001.0f,
		300001.0f, -300001.0f, -300001.0f,
		300001.0f, -300001.0f, -300001.0f,
		-300001.0f, -300001.0f, 300001.0f,
		300001.0f, -300001.0f, 300001.0f
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

}

void Skybox::updatePerspective(int width, int height)
{
	skyboxPerspective = perspective(45.0f, (float)width / (float)height, 0.1f, 1000000.0f);
}

void Skybox::draw(mat4 view)
{
	texture->bind();
	glUseProgram(skyboxShader);
	glDepthMask(GL_FALSE);
	
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "projection"), 1, GL_FALSE, value_ptr(skyboxPerspective));
	
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
}
