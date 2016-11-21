#pragma once
#include "Group.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

using namespace glm;

const vec3 xAxis = vec3(1, 0, 0);
const vec3 yAxis = vec3(0, 1, 0);
const vec3 zAxis = vec3(0, 0, 1);

class MatrixTransform: public Group
{
public:
	static mat4 trackballRotate(vec3 from, vec3 to);
	static vec3 trackballMap(double x, double y);
	
	mat4 M;

	MatrixTransform();
	MatrixTransform(mat4 M);

	void draw(mat4 C) override;
	void translate(float x, float y, float z);
	void translate(mat4 T);
	void scale(float amount);
	void scale(float amountX, float amountY, float amountZ);
	void rotateX(float degrees);
	void rotateY(float degrees);
	void rotateZ(float degrees);
	void rotate(float degreesX, float degreesY, float degreesZ);
	void rotate(mat4 R);
	void reset();
	void set(mat4 m);

};
