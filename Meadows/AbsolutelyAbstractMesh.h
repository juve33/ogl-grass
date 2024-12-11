#ifndef ABSOLUTELY_ABSTRACT_MESH_CLASS_H
#define ABSOLUTELY_ABSTRACT_MESH_CLASS_H

#include<string>

#include"VAO.h"
#include"Buffer.h"
#include"Camera.h"
#include"Texture.h"

class AbsolutelyAbstractMesh
{
protected:
	// Store VAO so it can be used in the Draw function
	VAO VAO;
};

#endif