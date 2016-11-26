#pragma once
#include "Geode.h"
class Sphere :
	public Geode
{
public:
	Sphere();
	Sphere(Material* mat);
	Sphere(bool shrink);
	Sphere(Material* mat, bool shrink);
	static Model* generateSphere(int horizontalSegments, int verticalSegments, bool shrink);
};


