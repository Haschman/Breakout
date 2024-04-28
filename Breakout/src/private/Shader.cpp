#include "Shader.h"

#include <iostream>
#include <exception>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader()
{
    m_ID = glCreateProgram();
    if (m_ID == 0)
        throw std::runtime_error("Program could not be created. glCreateProgram returned 0\n");
}

Shader& Shader::Use()
{
    glUseProgram(m_ID);
    return *this;
}

void Shader::Compile(const char* sourceVert, const char* sourceFrag, const char* sourceGeo)
{
    unsigned int shaderVert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderVert, 1, &sourceVert, NULL);
    glCompileShader(shaderVert);
    checkCompileErrors(shaderVert, "VERTEX");

    unsigned int shaderFragm = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderFragm, 1, &sourceFrag, NULL);
    glCompileShader(shaderFragm);
    checkCompileErrors(shaderFragm, "FRAGMENT");

    unsigned int shaderGeo;
    if (sourceGeo != nullptr) {
        shaderGeo = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(shaderGeo, 1, &sourceGeo, NULL);
        glCompileShader(shaderGeo);
        checkCompileErrors(shaderGeo, "GEOMETRY");
    }

    glAttachShader(m_ID, shaderVert);
    glAttachShader(m_ID, shaderFragm);
    if (sourceGeo != nullptr)
        glAttachShader(m_ID, shaderGeo);
    glLinkProgram(m_ID);
    checkCompileErrors(m_ID, "PROGRAM");

    glDeleteShader(shaderVert);
    glDeleteShader(shaderFragm);
    if (sourceGeo != nullptr)
        glDeleteShader(shaderGeo);
}

void Shader::SetFloat(const char* name, float value, bool useShader)
{
    if (useShader)
        Use();
    glUniform1f(glGetUniformLocation(m_ID, name), value);
}
void Shader::SetInteger(const char* name, int value, bool useShader)
{
    if (useShader)
        Use();
    glUniform1i(glGetUniformLocation(m_ID, name), value);
}
void Shader::SetVector2f(const char* name, float x, float y, bool useShader)
{
    if (useShader)
        Use();
    glUniform2f(glGetUniformLocation(m_ID, name), x, y);
}
void Shader::SetVector2f(const char* name, const glm::vec2& value, bool useShader)
{
    if (useShader)
        Use();
    glUniform2f(glGetUniformLocation(m_ID, name), value.x, value.y);
}
void Shader::SetVector3f(const char* name, float x, float y, float z, bool useShader)
{
    if (useShader)
        Use();
    glUniform3f(glGetUniformLocation(m_ID, name), x, y, z);
}
void Shader::SetVector3f(const char* name, const glm::vec3& value, bool useShader)
{
    if (useShader)
        Use();
    glUniform3f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool useShader)
{
    if (useShader)
        Use();
    glUniform4f(glGetUniformLocation(m_ID, name), x, y, z, w);
}
void Shader::SetVector4f(const char* name, const glm::vec4& value, bool useShader)
{
    if (useShader)
        Use();
    glUniform4f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader)
{
    if (useShader)
        Use();
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, false, glm::value_ptr(matrix));
}

unsigned int Shader::GetID() const
{
    return m_ID;
}


void Shader::checkCompileErrors(unsigned int object, const std::string &type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------- --"
                << std::endl;
        }
    }
    else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::PROGRAM: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------- --"
                << std::endl;
        }
    }
}
