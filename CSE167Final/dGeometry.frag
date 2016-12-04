#version 330 core
//out vec4 Color;

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;


struct Material
{
	vec3 diffuseCoeff;
	float specularExp;
	vec3 ambientCoeff;
	float reflectivity;
};

uniform Material material;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

//uniform sampler2D modelTexture;

void main()
{    

	//Color = vec4(normalize(Normal), 1.0f);
    // Store the fragment position vector in the first gbuffer texture
    gPosition = FragPos;
	
	//gPosition = FragPos;
    // Also store the per-fragment normals into the gbuffer
    gNormal = normalize(Normal);
    // And the diffuse per-fragment color
    gAlbedoSpec.rgb = material.diffuseCoeff; //texture(modelTexture, TexCoords).rgb + material.diffuseCoeff;
    // Store specular intensity in gAlbedoSpec's alpha component
    gAlbedoSpec.a = material.specularExp;
	/**/
}