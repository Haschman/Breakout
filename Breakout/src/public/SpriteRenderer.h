#pragma once

#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"

class SpriteRenderer {
public:
    SpriteRenderer(Shader& shader);
    ~SpriteRenderer();
    
    void DrawSprite(const Texture2D& texture, const glm::vec2 &position,
        const glm::vec2 &size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
        const glm::vec3 &color = glm::vec3(1.0f));

private:
    Shader m_shader;
    unsigned int m_quadVAO;
    
    void initRenderData();
};
