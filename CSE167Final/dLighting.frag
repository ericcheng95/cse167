#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform vec3 cameraPos;

struct DirectionalLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirectionalLight directionalLight;

void main()
{   


    // Retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

	if (Normal.x == 0 && Normal.y == 0 && Normal.z == 0){
		FragColor = vec4(0,0,0,0);
	}
	else {
		vec3 viewDir  = normalize(cameraPos - FragPos);
		vec3 lightDir = normalize(-directionalLight.direction);
		vec3 ambient  = directionalLight.ambient;
		vec3 diffuse = max(dot(Normal, lightDir), 0.0f) * Diffuse * directionalLight.diffuse;
		vec3 halfway = normalize(viewDir + lightDir);
		vec3 specular = directionalLight.specular * pow(max(dot(halfway, Normal), 0.0f), Specular * 10.0f);//16.0) * Specular;
		FragColor = vec4(ambient + diffuse + specular, 1.0f);
	}
}