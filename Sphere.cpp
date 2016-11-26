#include "Sphere.h"

Sphere::Sphere() : Geode()
{
	model = generateSphere(16, 24, true);
}

Sphere::Sphere(bool shrink = true) : Geode()
{
	model = generateSphere(16, 24, shrink);
}

Sphere::Sphere(Material* mat) : Geode(mat)
{
	model = generateSphere(16, 24, true);
}

Sphere::Sphere(Material* mat, bool shrink = true) : Geode(mat)
{
	model = generateSphere(16, 24, shrink);
}


Model* Sphere::generateSphere(int horizontalSegments, int verticalSegments, bool shrink)
{
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
	float scale = 1.0f;
	if (shrink)
	{
		scale = 0.1f;
	}

	//Top vertex
	for (int j = 0; j < verticalSegments; j++)
	{
		vertices.push_back(0);
		vertices.push_back(1 * scale);
		vertices.push_back(0);
	}

	//rings
	float hAngle = 3.1415926 / horizontalSegments;
	float vAngle = 2 * 3.1415926 / verticalSegments;
	float x, y, z, r;
	for (int i = 1; i < horizontalSegments; i++)
	{
		y = cos(hAngle * i);
		r = sin(hAngle * i);
		for (int j = 0; j < verticalSegments; j++)
		{
			z = sin(vAngle * j) * r; 
			x = cos(vAngle * j) * r;
			vertices.push_back(x*scale);
			vertices.push_back(y*scale);
			vertices.push_back(z*scale);
		}
	}
	//Bottom vertex
	for (int j = 0; j < verticalSegments; j++)
	{
		vertices.push_back(0);
		vertices.push_back(-1 * scale);
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

	return new Model(vertices, vertices, faceVertexIndices);
}
