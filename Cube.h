#pragma once
#include "Geode.h"

class Cube :
	public Geode
{
public:
	Cube(unsigned int shader) : Geode(new Model("cube.obj"), shader)
	{
	};

	Cube(unsigned int shader, Material* mat) : Geode(new Model("cube.obj"), shader, mat)
	{
	};
};
