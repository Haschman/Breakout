#include "ResourceManager.h"
#include "shader.frag.h"
#include "shader.vert.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <glad/glad.h>

#include "stb_image.h"


std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char* shaderFileVert, const char* shaderFileFrag, const char* shaderFileGeo, const std::string &name)
{
    Shaders[name] = loadShaderFromFile(shaderFileVert, shaderFileFrag, shaderFileGeo);
    return Shaders[name];
}

Shader ResourceManager::LoadShader(const std::string &name)
{
    Shader shader;
    shader.Compile(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE, nullptr);
    Shaders[name] = shader;
    return Shaders[name];
}

Shader& ResourceManager::GetShader(const std::string &name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTextureFromPNGFile(const char* file, bool alpha, const std::string &name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::LoadTextureFromHeader(const unsigned char* image, int imageSize, bool alpha, const std::string &name)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load_from_memory(image, imageSize, &width, &height, &nrChannels, 0);

    Texture2D texture;
    if (alpha) {
        texture.SetInternalFormat(GL_RGBA);
        texture.SetImageFormat(GL_RGBA);
    }
    texture.Generate(width, height, data);

    stbi_image_free(data);

    Textures[name] = texture;
    return Textures[name];
}

Texture2D& ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    for (auto& iter : Shaders)
        glDeleteProgram(iter.second.GetID());
    for (auto& iter : Textures)
        glDeleteProgram(iter.second.GetID());
}

Shader ResourceManager::loadShaderFromFile(const char* shaderFileVert, const char* shaderFileFrag, const char* shaderFileGeo)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try {
        std::ifstream vertShaderFile(shaderFileVert);
        std::ifstream fragShaderFile(shaderFileFrag);

        std::stringstream vertShaderStream, fragShaderStream;
        vertShaderStream << vertShaderFile.rdbuf();
        fragShaderStream << fragShaderFile.rdbuf();

        vertShaderFile.close();
        fragShaderFile.close();

        vertexCode = vertShaderStream.str();
        fragmentCode = fragShaderStream.str();

        if (shaderFileGeo != nullptr) {
            std::ifstream geoShaderFile(shaderFileGeo);
            std::stringstream geoShaderStream;
            geoShaderStream << geoShaderFile.rdbuf();
            geoShaderFile.close();
            geometryCode = geoShaderStream.str();
        }
    }
    catch (std::exception e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();
    const char* geometryShaderCode = nullptr;
    if (shaderFileGeo != nullptr)
        geometryShaderCode = geometryCode.c_str();

    Shader shader;
    shader.Compile(vertexShaderCode, fragmentShaderCode, geometryShaderCode != nullptr ? geometryShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
    Texture2D texture;
    if (alpha) {
        texture.SetInternalFormat(GL_RGBA);
        texture.SetImageFormat(GL_RGBA);
    }
    
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    texture.Generate(width, height, data);
    
    stbi_image_free(data);
    return texture;
}
