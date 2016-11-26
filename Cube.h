#pragma once
#include "Geode.h"

class Cube :
	public Geode
{
public:
	Cube() : Geode(new Model("cube.obj"))
	{
	};

	Cube(Material* mat) : Geode(new Model("cube.obj"), mat)
	{
	};
};
