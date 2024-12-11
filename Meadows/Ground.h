#ifndef GROUND_CLASS_H
#define GROUND_CLASS_H

#include"AbstractMesh.h"

class Ground : public AbstractMesh
{
public:
	// Initializes the mesh
	Ground();
	Ground(std::string texturesDirectory);
};

#endif