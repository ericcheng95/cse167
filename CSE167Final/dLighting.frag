#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D ssao;

uniform vec3 cameraPos;

struct DirectionalLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirectionalLight directionalLight;

/*
struct Light {
    vec3 Position;
    vec3 Color;
    
    float Linear;
    float Quadratic;
};
const int NR_LIGHTS = 32;
uniform Light lights[NR_LIGHTS];
*/

void main()
{   


    // Retrieve data from gbuffer
    vec3 FragPos = texture(gPositionDepth, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedo, TexCoords).rgb;
    float Specular = texture(gAlbedo, TexCoords).a;
	float Depth = texture(gPositionDepth, TexCoords).a;
    float AmbientOcclusion = texture(ssao, TexCoords).r;

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
	
	
/*
    // Then calculate lighting as usual
    vec3 lighting  = Diffuse * 0.1; // hard-coded ambient component
    vec3 viewDir  = normalize(cameraPos - FragPos);
    for(int i = 0; i < NR_LIGHTS; ++i)
    {
        // Diffuse
        vec3 lightDir = normalize(lights[i].Position - FragPos);
        vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].Color;
        // Specular
        vec3 halfwayDir = normalize(lightDir + viewDir);  
        float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
        vec3 specular = lights[i].Color * spec * Specular;
        // Attenuation
        float distance = length(lights[i].Position - FragPos);
        float attenuation = 1.0 / (1.0 + lights[i].Linear * distance + lights[i].Quadratic * distance * distance);
        diffuse *= attenuation;
        specular *= attenuation;
        lighting += diffuse + specular;
    }    
    FragColor = vec4(lighting, 1.0);
*/
}