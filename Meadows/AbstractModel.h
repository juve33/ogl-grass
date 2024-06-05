#ifndef ABSTRACT_MODEL_CLASS_H
#define ABSTRACT_MODEL_CLASS_H

// do NOT include anything above Mesh.h bc it'll cause a linking error
#include"Mesh.h"


class AbstractModel
{
public:
	void Draw(Shader& shader, Camera& camera);

protected:
	// All the meshes and transformations
	std::vector<Mesh> meshes;
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;

	// Prevents textures from being loaded twice
	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	// Assembles all the floats into vertices
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions, 
		std::vector<glm::vec3> normals, 
		std::vector<glm::vec2> texUVs
	);

	// Utility: helps with the assembly from above by grouping floats
	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	// Utility: helps with the assembly from above by grouping floats
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	// Utility: helps with the assembly from above by grouping floats
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};
#endif