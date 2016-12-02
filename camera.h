#pragma once
#include "main.h"

class Camera
{
public:
	static vec3 cam_pos, cam_look_at, cam_up, cam_right;
	static vec3 cameraFrustumNormalLeft, cameraFrustumNormalRight, cameraFrustumNormalTop, cameraFrustumNormalBottom, cameraFrustumNormalNear, cameraFrustumNormalFar;
	static vec3 cameraFrustumPointLeft, cameraFrustumPointRight, cameraFrustumPointTop, cameraFrustumPointBottom, cameraFrustumPointNear, cameraFrustumPointFar;
	static int uProjection, uView, uCamera;
	static mat4 P;
	static mat4 V;

	static void init(unsigned int shader);
	static void enable();
	static void reset();
	static void updateV();
	static void updateP();


	static vec3 trackballMap(double x, double y);
	static mat4 trackballRotate(vec3 from, vec3 to);
};