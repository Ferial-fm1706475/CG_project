//-----------------------------------------------------------------------------
// Mesh.h
// Basic OBJ file importer
//-----------------------------------------------------------------------------
#ifndef MESH_H
#define MESH_H

using namespace std;

#include <vector>
#include <string>
#define GLEW_STATIC
#include "GL/glew.h"	// Important - this header must come before glfw3 header
#include "ShaderProgram.h"
#include "Texture.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;

	glm::vec3 Tangent;
	glm::vec3 Bitangent;

	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

class Mesh
{
public:

	Mesh(vector<Vertex>& mVertices, vector<GLuint>& mIndices, vector<Texture>& mTextures);

	~Mesh();

	void draw(ShaderProgram& shader); 
	//{
	//	// bind appropriate textures
	//	unsigned int diffuseNr = 1;
	//	unsigned int specularNr = 1;
	//	unsigned int normalNr = 1;
	//	unsigned int heightNr = 1;
	//	for (unsigned int i = 0; i < mTextures.size(); i++)
	//	{
	//		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
	//		// retrieve texture number (the N in diffuse_textureN)
	//		string number;
	//		string name = mTextures[i].type;
	//		if (name == "texture_diffuse")
	//			number = std::to_string(diffuseNr++);
	//		else if (name == "texture_specular")
	//			number = std::to_string(specularNr++); // transfer unsigned int to string
	//		else if (name == "texture_normal")
	//			number = std::to_string(normalNr++); // transfer unsigned int to string
	//		else if (name == "texture_height")
	//			number = std::to_string(heightNr++); // transfer unsigned int to string
	//
	//		// now set the sampler to the correct texture unit
	//		glUniform1i(glGetUniformLocation(shader.getProgram(), (name + number).c_str()), i);
	//		// and finally bind the texture
	//		glBindTexture(GL_TEXTURE_2D, mTextures[i].id);
	//	}

	//	glBindVertexArray(mVAO);
	//	glDrawElements(GL_TRIANGLES, static_cast<GLuint>(mIndices.size()), GL_UNSIGNED_INT, 0);
	//	glBindVertexArray(0);

	//	glActiveTexture(GL_TEXTURE0);
	//}
	

private:
	GLuint mVAO, mVBO, mIBO;
	void initBuffers(vector<Vertex>& mVertices, vector<GLuint>& mIndices);
	vector<Texture> mTextures;
	vector<GLuint>mIndices = mIndices;

};
#endif //MESH_H
