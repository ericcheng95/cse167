#include "Model.h"

Model::Model(vector<GLfloat>& vertices, vector<GLfloat>& normals, vector<GLuint>& faceVertexIndices)
{
	count = faceVertexIndices.size();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBON);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], g_BufferUsage);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBON);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], g_BufferUsage);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faceVertexIndices.size() * sizeof(GLuint), &faceVertexIndices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model::updateData(vector<GLfloat>& vertices, vector<GLfloat>& normals)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(GLfloat), &vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBON);
	glBufferSubData(GL_ARRAY_BUFFER, 0, normals.size() * sizeof(GLfloat), &normals[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::updateData(vector<GLfloat>& vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(GLfloat), &vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Model::Model(char* filepath)
{
	vector<GLfloat> vertices, normals;
	vector<GLuint> faceVertexIndices;
	FILE* fp; // file pointer
	GLfloat x, y, z; // vertex coordinates
	GLuint xi, yi, zi, xn, yn, zn; // vertex color
	int c1, c2; // characters read from file
	fp = fopen(filepath, "rb"); // make the file name configurable so you can load other files
	if (fp == nullptr) { cout << "error loading file " << filepath << endl; } // just in case the file can't be found or is corrupt
	cout << "Loading..." << endl;
	while (!feof(fp))
	{
		c1 = fgetc(fp);
		if (c1 == 'f')
		{
			fgetc(fp);
			fscanf(fp, "%d//%d %d//%d %d//%d", &xi, &xn, &yi, &yn, &zi, &zn);
			faceVertexIndices.push_back(xi - 1);
			faceVertexIndices.push_back(yi - 1);
			faceVertexIndices.push_back(zi - 1);
		}
		else if (c1 == 'v')
		{
			c2 = fgetc(fp);
			if (c2 == ' ')
			{
				fscanf(fp, "%f %f %f", &x, &y, &z);
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			}
			else if (c2 == 'n' && fgetc(fp) == ' ')
			{
				fscanf(fp, "%f %f %f", &x, &y, &z);
				normals.push_back(x);
				normals.push_back(y);
				normals.push_back(z);
			}
		}
		while (!feof(fp) && fgetc(fp) != '\n');
	}
	fclose(fp);

	count = faceVertexIndices.size();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBON);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], g_BufferUsage);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, VBON);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], g_BufferUsage);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faceVertexIndices.size() * sizeof(GLuint), &faceVertexIndices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


Model::~Model()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBON);
	glDeleteBuffers(1, &EBO);
}

void Model::draw()
{
	glPolygonMode(g_PolygonFace, g_PolygonMode);
	glBindVertexArray(VAO);
	glDrawElements(g_DrawMode, count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
