#version 330 core
//out vec4 Color;

layout (location = 0) out vec4 gPositionDepth;
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


float near = 1.0; 
float far = 1000.0; 
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{    

	// Store the fragment position vector in the first gbuffer texture
    gPositionDepth.xyz = FragPos;
    // And store linear depth into gPositionDepth's alpha component
    gPositionDepth.a = LinearizeDepth(gl_FragCoord.z); // Divide by far to store depth in range 0.0 - 1.0
    // Also store the per-fragment normals into the gbuffer
    gNormal = normalize(Normal);
    // And the diffuse per-fragment color
    gAlbedoSpec.rgb = material.diffuseCoeff; //texture(modelTexture, TexCoords).rgb + material.diffuseCoeff;
    // Store specular intensity in gAlbedoSpec's alpha component
    gAlbedoSpec.a = material.specularExp;
	/**/

	

}