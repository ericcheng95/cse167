#version 330 core
// This is a sample fragment shader.

struct Material
{
	vec3 diffuseCoeff;
	float shininessExp;
	vec3 specularCoeff;
	vec3 ambientCoeff;
	float reflectivity;
};

struct DirectionalLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float attenuation;
};


struct SpotLight
{
	vec3 direction;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float attenuation;
	float spotCutoff;
	float spotExponent;
};

uniform Material material;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
in vec3 FragPos;
in vec3 Normal;
in vec3 RawNormal;

uniform vec3 cameraPos;
uniform samplerCube skybox;

// You can output many things. The first vec4 type output determines the color of the fragment
out vec4 color;

void main()
{
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(cameraPos - FragPos);

	vec3 I = -1.0f * viewDir;
	vec3 R = reflect(I, normal);
	vec4 textureColor = texture(skybox, R);

	//if (lightType == 0){ //directional
		vec3 lightDir = normalize(-directionalLight.direction);
		vec3 ambient  = directionalLight.ambient * material.ambientCoeff;
		vec3 diffuse = directionalLight.diffuse * max(dot(normal, lightDir), 0.0f) * material.diffuseCoeff;
		vec3 halfway = normalize(viewDir + lightDir);
		vec3 specular = directionalLight.specular * pow(max(dot(halfway, normal), 0.0f), material.shininessExp);
		color = vec4(ambient + diffuse + specular, 1.0f) + material.reflectivity * textureColor;
	/*}
	else if (lightType == 1) {//point
		vec3 lightVector = pointLight.position - FragPos;
		vec3 lightDir = normalize(lightVector);

		vec3 ambient  = pointLight.ambient * material.ambientCoeff;
		vec3 diffuse = pointLight.diffuse * max(dot(normal, lightDir),  0.0f) * material.diffuseCoeff;
		vec3 halfway = normalize(viewDir + lightDir);
		vec3 specular = pointLight.specular * pow(max(dot(halfway, normal), 0.0f), material.shininessExp);
		float distance = length(lightVector);
		color = vec4((ambient + diffuse + specular) / (pointLight.attenuation * distance * distance), 1.0f) + material.reflectivity * textureColor;
	}
	else {
		vec3 lightVector = spotLight.position - FragPos;
		vec3 lightDir = normalize(lightVector);
		float falloff = -dot(lightDir, normalize(spotLight.direction));
		if (falloff > cos(spotLight.spotCutoff)){
				vec3 ambient  = spotLight.ambient * material.ambientCoeff;
				vec3 diffuse = spotLight.diffuse * max(dot(normal, lightDir),  0.0f) * material.diffuseCoeff;
				vec3 halfway = normalize(viewDir + lightDir);
				vec3 specular = spotLight.specular * pow(max(dot(halfway, normal), 0.0f), material.shininessExp);
				float distance = length(lightVector);
				color = vec4((ambient + diffuse + specular) / (spotLight.attenuation * distance * distance) * pow(falloff, spotLight.spotExponent), 1.0f) + material.reflectivity * textureColor;
		}
		else {
			color = vec4(0, 0, 0, 1.0f);
		}
	}*/
	
}
