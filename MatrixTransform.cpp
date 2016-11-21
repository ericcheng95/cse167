#include "MatrixTransform.h"

MatrixTransform::MatrixTransform()
{
	M = mat4(1.0f);
}

MatrixTransform::MatrixTransform(mat4 m)
{
	M = m;
}

void MatrixTransform::draw(mat4 C)
{
	mat4 CM = C * M;
	for (auto it = children.begin(); it != children.end(); it++)
	{
		(*it)->draw(CM);
	}
}

void MatrixTransform::reset()
{
	M = mat4(1.0f);
}

void MatrixTransform::set(mat4 m)
{
	M = m;
}

void MatrixTransform::translate(float x, float y, float z)
{
	M = glm::translate(vec3(x, y, z)) * M;
}

void MatrixTransform::translate(mat4 T)
{
	M = T * M;
}

void MatrixTransform::scale(float amount)
{
	M = amount * M;
}

void MatrixTransform::scale(float amountX, float amountY, float amountZ)
{
	M = glm::scale(vec3(amountX, amountY, amountZ)) * M;
}

void MatrixTransform::rotateX(float radians)
{
	M = glm::rotate(radians, xAxis) * M;
}

void MatrixTransform::rotateY(float radians)
{
	M = glm::rotate(radians, yAxis) * M;
}

void MatrixTransform::rotateZ(float radians)
{
	M = glm::rotate(radians, zAxis) * M;
}

void MatrixTransform::rotate(float radiansX, float radiansY, float radiansZ)
{
	M = glm::rotate(radiansX, xAxis) * glm::rotate(radiansY, yAxis) * glm::rotate(radiansZ, zAxis) * M;
}

void MatrixTransform::rotate(mat4 R)
{
	M = R * M;
}

vec3 MatrixTransform::trackballMap(double x, double y)
{
	x = (2 * x - Window::width) / Window::width;
	y = (Window::height - 2 * y) / Window::height;
	double dSquare = x * x + y * y;
	if (dSquare > 1.0)
	{
		dSquare = 1.0;
	}
	return normalize(glm::vec3(x, y, sqrt(1.0 - dSquare)));
}

mat4 MatrixTransform::trackballRotate(glm::vec3 from, glm::vec3 to)
{
	return glm::rotate(length(to - from) * 9, cross(from, to));
}
