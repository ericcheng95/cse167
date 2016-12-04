#pragma once
#include "main.h"
#include "Material.h"
#include "texture.h"
#include "Face.h"

using namespace std;

/*
*
* ALL MODELS MUST BE CONVEX!!
* (Each edge must only have up to 2 faces also)
*
*/


class Model
{
public:

	int g_DrawMode = GL_TRIANGLES;
	int g_PolygonMode = GL_FILL; //point, line , fill
	int g_PolygonFace = GL_FRONT_AND_BACK; //front, back, front and back
	int g_BufferUsage = GL_STATIC_DRAW;
	Texture* texture;//Texture to use, if provided
	float minX = 999999.9f, minY = 999999.9f, minZ = 999999.9f, maxX = -999999.9f, maxY = -999999.9f, maxZ = -999999.9f;//for culling

	vector<GLfloat> vertices, normals, textures;
	vector<GLuint> faceVertexIndices, textureIndices;
	vector<Face*> faces;
	vector<Segment*> segments;


	void draw();
//	void updateData(vector<GLfloat>& vertices);
//	void updateData(vector<GLfloat>& vertices, vector<GLfloat>& normals);
	Model(vector<GLfloat>& vertices, vector<GLfloat>& normals, vector<GLuint>& faceVertexIndices);
	Model(char* filepath);
	Model(char* filepath, Texture* texture);
	~Model();

private:
	unsigned int VBO, VBON, VAO, EBO, VBOT;
	int count;
	bool hasTextureCoords = false;

	void findMinMax(vector<GLfloat>& vertices);
	void computeFaceSegments();
};
