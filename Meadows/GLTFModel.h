#ifndef GLTFMODEL_CLASS_H
#define GLTFMODEL_CLASS_H

#include"AbstractModel.h"
#include<json/json.h>

using json = nlohmann::json;


class GLTFModel : public AbstractModel
{
public:
	GLTFModel();
	// Loads in a model from a file and stores the information in 'data', 'JSON', and 'file'
	GLTFModel(const char* file);

private:
	// Variables for easy access
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	// Prevents textures from being loaded twice
	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	// Loads a single mesh by its index
	void loadMesh(unsigned int indMesh);

	// Traverses a node recursively, so it essentially traverses all connected nodes
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	// Gets the binary data from a file
	std::vector<unsigned char> getData();
	// Interprets the binary data into floats, indices, and textures
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();
};
#endif
