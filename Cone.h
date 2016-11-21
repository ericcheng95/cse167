#pragma once
#include "Geode.h"

class Cone : public Geode {
public:
	Cone(unsigned int shader) : Geode(new Model("cone.obj"), shader) {};
	Cone(unsigned int shader, Material* mat) : Geode(new Model("cone.obj"), shader, mat) {};
};
