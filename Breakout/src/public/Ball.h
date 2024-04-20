#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "Texture.h"


class Ball : public GameObject {
public:
    Ball();
    Ball(float radius, glm::vec2 pos, glm::vec2 velocity, Texture2D sprite);

    glm::vec2 Move(float delta, unsigned int window_width, unsigned int window_height);
    void Reset(glm::vec2 position, glm::vec2 velocity);
    float getRadius() const;

private:
    float m_radius;
};