//#include "texture.h"
////texture rendering
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb-master/stb_image.h"
//
//Texture::Texture() : mTexture(0) {}
//
//Texture::~Texture() {
//	glDeleteTextures(1, &mTexture);
//}//enables overload that function/method 
//
//bool Texture::loadTexture(const string& filename, bool generateMipMap) {
//	//****************************
//	unsigned int diffuseNr = 1;
//	unsigned int specularNr = 1;
//	unsigned int normalNr = 1;
//	unsigned int heightNr = 1;
//	//******************************************************************
//	
//	GLint width, height, nrComponents;
//	string name, number;
//
//	if (filename.find("texture_diffuse") != std::string::npos) {
//		type = name = "diffuse"; 
//		number = std::to_string(diffuseNr++);
//	}
//	else if (filename.find("texture_specular") != std::string::npos) {
//		type = name= "specular";
//		number = std::to_string(specularNr++); // transfer unsigned int to string
//	}
//	else if (filename.find("texture_normal") != std::string::npos) {
//		type = name = "normal";
//		number = std::to_string(normalNr++); // transfer unsigned int to string
//	}
//	else if (filename.find("texture_height") != std::string::npos) {
//		type = name = "height";
//		number = std::to_string(heightNr++); // transfer unsigned int to string
//	}
//	else {
//		type = name = "unknown";
//	}
//	
//	glGenTextures(1, &mTexture);
//	glBindTexture(GL_TEXTURE_2D, mTexture);
//
//	//set parameters 
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	//set texture filtering 
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	stbi_set_flip_vertically_on_load(true);
//
//	//load texture from file
//	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
//
//	GLenum format = GL_RGB;
//	if (nrComponents == 1)
//		format = GL_RED;
//	if (nrComponents == 3)
//		format = GL_RGB;
//	if (nrComponents == 4)
//		format = GL_RGBA;
//
//	if (!data) {
//		printf("Failing to load image %s\n", filename.c_str());
//	}
//	if (generateMipMap)
//		glGenerateMipmap(GL_TEXTURE_2D); //optinal 
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//	stbi_image_free(data);
//	//******************************************************************
//	return true;
//
//}
//
//void Texture::bind(GLuint texUnit) {
//	glActiveTexture(GL_TEXTURE0 + texUnit);
//	glBindTexture(GL_TEXTURE_2D, mTexture);
//}
//
//void Texture::unbind(GLuint texUnit) {
//	glActiveTexture(GL_TEXTURE0 + texUnit);
//	glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//string Texture::getType() const {
//	return type;
//}
