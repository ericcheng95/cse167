#include "Light.h"

DirectionalLight Light::l = { vec3(0, -1, -1), vec3(0.75, 0.75, 0.75), vec3(0.75, 0.75, 0.75), vec3(0.75, 0.75, 0.75) };

//directionalLight = 
//pointLight = { vec3(0, 12, 0), vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), 0.02f };
//spotLight = { vec3(0, -1, 0), vec3(0, 12, 0), vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), 0.02f, 3.1415f / 72.0f ,64 };
