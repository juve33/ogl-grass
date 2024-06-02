#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 crntPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;

in DATA
{
    vec3 Normal;
	vec3 color;
	vec2 texCoord;
    mat4 projection;
} data_in[];


// Default main function
void main()
{
    // I found multiple sources that stated that array indexes have to be constants, but for some reason this works perfectly fine on my computer... maybe this will break something in the future...

    for(int i=0;i<=2;i++)
    {
        gl_Position = data_in[i].projection * gl_in[i].gl_Position;
        crntPos = vec3(gl_in[i].gl_Position);
        Normal = data_in[i].Normal;
        color = data_in[i].color;
        texCoord = data_in[i].texCoord;
        EmitVertex();
    }

    EndPrimitive();
}