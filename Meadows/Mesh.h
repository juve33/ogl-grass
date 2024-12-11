#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include"AbstractMesh.h"

class Mesh : public AbstractMesh
{
public:
	// Initializes the mesh
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures);
};

#endif