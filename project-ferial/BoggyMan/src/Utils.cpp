#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

#include "Utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

Utils::Utils() {}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int Utils::loadTexture(const char *texImagePath)
{
    unsigned int textureID = 0;
    int width, height, nrComponents;
    
    unsigned char *data = stbi_load(texImagePath, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = 0;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << texImagePath << std::endl;
        stbi_image_free(data);
    }
    return textureID;
}

// load texture from file using path and filename used in mode.h
unsigned int Utils::loadTextureFromFile( const char *path, string directory )
{
    string filename = string( path );
    filename = directory + '/' + filename;
//    cout << filename << endl; //<-- Do this

    unsigned int textureID = 0;
    int width, height, nrComponents;
    
    unsigned char *data = stbi_load(filename.c_str() , &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = 0;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << filename.c_str() << std::endl;
        stbi_image_free(data);
    }
    return textureID;
}


//GLuint Utils::loadTexture(const char *texImagePath)
//{
//    GLuint textureRef;
//
//
//    textureRef = SOIL_load_OGL_texture(texImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
//    if (textureRef == 0) cout << "didnt find texture file " << texImagePath << endl;
//    // ----- mipmap/anisotropic section
//    glBindTexture(GL_TEXTURE_2D, textureRef);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glGenerateMipmap(GL_TEXTURE_2D);
//    if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
//        GLfloat anisoset = 0.0f;
//        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoset);
//        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoset);
//    }
//    // ----- end of mipmap/anisotropic section
//    return textureRef;
//}
