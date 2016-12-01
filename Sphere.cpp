#include "Sphere.h"

Sphere::Sphere() : Geode()
{
	model = generateSphere(16, 24);
}

Sphere::Sphere(Material* mat) : Geode(mat)
{
	model = generateSphere(16, 24);
}

Model* Sphere::generateSphere(int horizontalSegments, int verticalSegments)
{
	static Model* model;
	if (model != nullptr)
	{
		return model;
	}

	if (horizontalSegments < 2)
	{
		horizontalSegments = 2;
	}
	if (verticalSegments < 3)
	{
		verticalSegments = 3;
	}
	vector<GLfloat> vertices, normals;
	vector<GLuint> faceVertexIndices;

	//Top vertex
	for (int j = 0; j < verticalSegments; j++)
	{
		vertices.push_back(0);
		vertices.push_back(1);
		vertices.push_back(0);
	}

	//rings
	float hAngle = 3.1415926f / horizontalSegments;
	float vAngle = 2.0f * 3.1415926f / verticalSegments;
	float x, y, z, r;
	for (int i = 1; i < horizontalSegments; i++)
	{
		y = cos(hAngle * i);
		r = sin(hAngle * i);
		for (int j = 0; j < verticalSegments; j++)
		{
			z = sin(vAngle * j) * r; 
			x = cos(vAngle * j) * r;
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
		}
	}
	//Bottom vertex
	for (int j = 0; j < verticalSegments; j++)
	{
		vertices.push_back(0);
		vertices.push_back(-1);
		vertices.push_back(0);
	}

	int startingIndex = 1;

	//For each ring
	for (int i = 0; i <= horizontalSegments; i++)
	{
		startingIndex = i * verticalSegments;
		for (int j = 0; j < verticalSegments-1; j++) {
			faceVertexIndices.push_back(startingIndex + j); //a
			faceVertexIndices.push_back(startingIndex + j - verticalSegments); //b
			faceVertexIndices.push_back(startingIndex + j + 1); //d
			faceVertexIndices.push_back(startingIndex + j - verticalSegments); //b
			faceVertexIndices.push_back(startingIndex + j - verticalSegments + 1); //c
			faceVertexIndices.push_back(startingIndex + j + 1); //d
		}
		// wrap around
		int j = verticalSegments - 1;
		faceVertexIndices.push_back(startingIndex + j); //a
		faceVertexIndices.push_back(startingIndex + j - verticalSegments); //b
		faceVertexIndices.push_back(startingIndex); //d
		faceVertexIndices.push_back(startingIndex + j - verticalSegments); //b
		faceVertexIndices.push_back(startingIndex - verticalSegments); //c
		faceVertexIndices.push_back(startingIndex); //d
	}
	model = new Model(vertices, vertices, faceVertexIndices);
	return model;
}
