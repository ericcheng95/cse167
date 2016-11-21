#pragma once
#include "main.h"


const vec3 xAxis = vec3(1, 0, 0);
const vec3 yAxis = vec3(0, 1, 0);
const vec3 zAxis = vec3(0, 0, 1);
Material* defaultMaterial = new Material{ vec3(1.0f, 1.0f, 1.0f), 10, vec3(1.0f, 1.0f, 1.0f), vec3(0.2f, 0.2f, 0.2f), 0.0f };

int geodeCounter = 1;
class Geode
{
public:
	int id;
	Model* model;
	Material* material;
	list<Geode*> children;
	mat4 M;
	
	Geode();
	Geode(Material* mat);
	Geode(Model* m);
	Geode(Model* m, Material* mat);
	Geode(mat4 M);
	Geode(Model* m, Material* mat, mat4 M);

	void draw(mat4 C, unsigned int shader);
	void translate(float x, float y, float z);
	void translate(mat4 T);
	void scale(float amountX, float amountY, float amountZ);
	void rotate(float degreesX, float degreesY, float degreesZ);
	void rotate(mat4 R);
	void reset();
	void set(mat4 m);


};

