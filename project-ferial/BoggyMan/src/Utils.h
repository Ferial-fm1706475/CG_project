#ifndef UTILS_H
#define UTILS_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <fstream>

class Utils
{
public:
	Utils();
	static GLuint loadTexture(const char *texImagePath);
    static GLuint loadTextureFromFile( const char *path, std::string directory );
};

#endif
