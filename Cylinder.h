#pragma once
#include "Geode.h"

class Cylinder : public Geode {
public:
	Cylinder(unsigned int shader) : Geode(new Model("cylinder.obj"), shader) {};
	Cylinder(unsigned int shader, Material* mat) : Geode(new Model("cylinder.obj"), shader, mat) {};
};
