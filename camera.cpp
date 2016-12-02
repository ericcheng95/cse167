#include "camera.h"
#include "PrimaryWindow.h"

vec3 Camera::cam_pos(0.0f, 0.0f, 1.0f);
vec3 Camera::cam_look_at(0.0f, 0.0f, 0.0f);
vec3 Camera::cam_up(0.0f, 1.0f, 0.0f);
vec3 Camera::cam_right(1.0f, 0.0f, 0.0f);
vec3 Camera::cameraFrustumNormalLeft, Camera::cameraFrustumNormalRight, Camera::cameraFrustumNormalTop, Camera::cameraFrustumNormalBottom, Camera::cameraFrustumNormalNear, Camera::cameraFrustumNormalFar;
vec3 Camera::cameraFrustumPointLeft, Camera::cameraFrustumPointRight, Camera::cameraFrustumPointTop, Camera::cameraFrustumPointBottom, Camera::cameraFrustumPointNear, Camera::cameraFrustumPointFar;

int Camera::uProjection, Camera::uView, Camera::uCamera;

mat4 Camera::P;
mat4 Camera::V;

void Camera::init(unsigned int shader)
{
	uProjection = glGetUniformLocation(shader, "projection");
	uView = glGetUniformLocation(shader, "view");
	uCamera = glGetUniformLocation(shader, "cameraPos");
}

void Camera::enable()
{
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &P[0][0]);
	glUniformMatrix4fv(uView, 1, GL_FALSE, &V[0][0]);
	glUniform3fv(uCamera, 1, &cam_pos[0]);
}

void Camera::reset()
{
	cam_pos = vec3(0, 0, 1.0f);
	cam_look_at = vec3(0.0f, 0.0f, 0.0f);
	updateV();
}

void Camera::updateV()
{
	V = lookAt(cam_pos, cam_look_at, cam_up);
	float pi = 3.1415926f;
	float hfar = tan(28.0f * pi / 180.0f) * 1000.0f;
	float wfar = hfar * PrimaryWindow::width / PrimaryWindow::height;

	vec3 direction = normalize(cam_look_at - cam_pos);

	vec3 right = normalize(cross(direction, vec3(0, 1, 0)));
	vec3 up = normalize(cross(right, direction));

	vec3 farCenter = cam_pos + direction * 1000.0f;

	cameraFrustumNormalFar = direction;
	cameraFrustumPointFar = cam_pos + direction * 1000.0f;
	cameraFrustumNormalNear = -direction;
	cameraFrustumPointNear = cam_pos + direction * 0.1f;;

	cameraFrustumNormalLeft = normalize(cross(normalize(farCenter + right * wfar - cam_pos), up));
	cameraFrustumPointLeft = cam_pos;
	cameraFrustumNormalRight = normalize(cross(up, normalize(farCenter - right * wfar - cam_pos)));
	cameraFrustumPointRight = cam_pos;

	cameraFrustumNormalTop = normalize(cross(right, normalize(farCenter + up * hfar - cam_pos)));
	cameraFrustumPointTop = cam_pos;
	cameraFrustumNormalBottom = normalize(cross(normalize(farCenter - up * hfar - cam_pos), right));
	cameraFrustumPointBottom = cam_pos;
}

void Camera::updateP()
{
	P = perspective(45.0f, (float)PrimaryWindow::width / (float)PrimaryWindow::height, 0.1f, 1000.0f);
}

vec3 Camera::trackballMap(double x, double y)
{
	x = (2 * x - PrimaryWindow::width) / PrimaryWindow::width;
	y = (PrimaryWindow::height - 2 * y) / PrimaryWindow::height;
	double dSquare = x * x + y * y;
	if (dSquare > 1.0)
	{
		dSquare = 1.0;
	}
	return normalize(vec3(x, y, sqrt(1.0 - dSquare)));
}

mat4 Camera::trackballRotate(vec3 from, vec3 to)
{
	return rotate(length(to - from), cross(from, to));
}
