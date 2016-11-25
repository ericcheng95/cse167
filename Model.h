#pragma once
#include "main.h"
#include "Material.h"

using namespace std;

class Model
{
public:

	int g_DrawMode = GL_TRIANGLES;
	int g_PolygonMode = GL_FILL; //point, line , fill
	int g_PolygonFace = GL_FRONT_AND_BACK; //front, back, front and back
	int g_BufferUsage = GL_STATIC_DRAW;

	void draw();
	void updateData(vector<GLfloat>& vertices);
	void updateData(vector<GLfloat>& vertices, vector<GLfloat>& normals);
	Model(vector<GLfloat>& vertices, vector<GLfloat>& normals, vector<GLuint>& faceVertexIndices);
	Model(char* filepath);
	~Model();

private:
	unsigned int VBO, VBON, VAO, EBO;
	int count;

};
