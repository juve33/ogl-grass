#version 460 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the current position from the Geometry Shader
in vec3 crntPos;
// Imports the normal from the Geometry Shader
in vec3 Normal;
// Imports the color from the Geometry Shader
in vec3 color;
// Imports the texture coordinates from the Geometry Shader
in vec2 texCoord;



// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightDir;
// Gets the color of the fog from the main function
uniform vec4 fogColor;
// Gets the position of the camera from the main function
uniform vec3 camPos;


vec4 direcLight()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	float diffuse = max(dot(normal, lightDir), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDir, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}


float near = 0.1f;
float far = 100.0f;

float linearizeDepth(float depth)
{
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth, float gradientLength = 65.0f, float offset = 30.0f)
{
	float zVal = linearizeDepth(depth);
	return (clamp(((zVal - offset) / gradientLength), 0.0f, 1.0f));
}


void main()
{
	float depth = logisticDepth(gl_FragCoord.z);
	// outputs final color
	FragColor = direcLight() * (1.0f - depth) + depth * fogColor;
}