#pragma once
#include "Geode.h"

class Pyramid : public Geode {
public:
	Pyramid(unsigned int shader) : Geode(new Model("pyramid.obj"), shader) {};
	Pyramid(unsigned int shader, Material* mat) : Geode(new Model("pyramid.obj"), shader, mat) {};
};

