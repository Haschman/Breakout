#pragma once

#include <map>
#include <string>

#include "Texture.h"
#include "Shader.h"


class ResourceManager {
public:
    static Shader LoadShader(const char* shaderFileVert, const char* shaderFileFrag, const char* shaderFileGeo, const std::string &name);
    static Shader LoadShader(const std::string &name);
    static Shader& GetShader(const std::string &name);

    static Texture2D LoadTextureFromPNGFile(const char* file, bool alpha, const std::string &name);
    static Texture2D LoadTextureFromHeader(const unsigned char* image, int imageSize, bool alpha, const std::string& name);
    static Texture2D& GetTexture(std::string name);

    // De-allocates all loaded resources
    static void Clear();

    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture2D> Textures;

private:
    ResourceManager() {};
    static Shader loadShaderFromFile(const char* shaderFileVert, const char* shaderFileFrag, const char* shaderFileGeo = nullptr);
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
};