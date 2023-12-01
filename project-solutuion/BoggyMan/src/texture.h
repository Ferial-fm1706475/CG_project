#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/glew.h"
#include <string>
using namespace std;

class Texture
{
public:
	Texture();
	virtual ~Texture(); //enables overload that function/method 

	bool loadTexture(const string& filename, bool generateMipMap);
	void bind(GLuint texUnit = 0);
	void unbind(GLuint texUnit);
	string getType() const;


private:
	GLuint mTexture;
	string type;
};

#endif // !TEXTURE_H
