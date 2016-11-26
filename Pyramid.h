#pragma once
#include "Geode.h"

class Pyramid : public Geode {
public:
	Pyramid() : Geode(new Model("pyramid.obj")) {};
	Pyramid(Material* mat) : Geode(new Model("pyramid.obj"), mat) {};
};

