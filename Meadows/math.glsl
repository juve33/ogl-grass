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