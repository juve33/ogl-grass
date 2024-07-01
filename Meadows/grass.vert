#version 460 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not necessarily normalized)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;


layout(binding = 0) buffer grass_data0
{
    vec2 displacement[];
};
layout(binding = 1) buffer grass_data1
{
    vec2 grassRotation[];
};
layout(binding = 2) buffer grass_data2
{
    float grassBending[];
};
layout(binding = 3) buffer grass_data3
{
    float grassHeight[];
};
layout(binding = 4) buffer grass_data4
{
    float test_float;
};


out DATA
{
    vec3 Normal;
	vec3 color;
	vec2 texCoord;
    mat4 projection;
} data_out;



// Imports the camera matrix
uniform mat4 camMatrix;
// Imports the transformation matrices
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
// Distance between grass blades
uniform float instanceDistance;
// Number of instances in a line per chunk
uniform int chunkSize;


mat4 rotationXmat4( in float angle )
{
	return mat4(
		1.0, 0, 0, 0,
		0, cos(angle), -sin(angle),	0,
		0, sin(angle), cos(angle), 0,
		0, 0, 0, 1
	);
}

mat3 rotationXmat3( in float angle )
{
	return mat3(
		1.0, 0, 0,
		0, cos(angle), -sin(angle),
		0, sin(angle), cos(angle)
	);
}

mat4 rotationYmat4( in vec2 SinCos )
{
	return mat4(
		SinCos.y,	0, SinCos.x, 0,
		0, 1.0, 0, 0,
		-SinCos.x, 0, SinCos.y,	0,
		0, 0, 0, 1
	);
}

mat3 rotationYmat3( in vec2 SinCos )
{
	return mat3(
		SinCos.y,	0, SinCos.x,
		0, 1.0, 0,
		-SinCos.x, 0, SinCos.y
	);
}


void main()
{
	float curveAmount = grassBending[gl_InstanceID] * aPos.y / (0.06 * grassHeight[gl_InstanceID]);
	vec2 disp = vec2(instanceDistance * (mod(gl_InstanceID, chunkSize) + displacement[gl_InstanceID].x), instanceDistance * ((gl_InstanceID / chunkSize) + displacement[gl_InstanceID].y));
	gl_Position = model * translation * rotation * scale * (vec4(disp.x, 0.0, disp.y, 0.0) + (rotationYmat4(grassRotation[gl_InstanceID]) * rotationXmat4(curveAmount) * vec4(aPos.x, aPos.y * grassHeight[gl_InstanceID] * test_float, aPos.z, 1.0f)));
	data_out.Normal = rotationYmat3(grassRotation[gl_InstanceID]) * rotationXmat3(curveAmount) * aNormal;
	data_out.color = aColor;
	data_out.texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
	data_out.projection = camMatrix;
}