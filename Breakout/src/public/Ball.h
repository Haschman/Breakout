#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "Texture.h"

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

class Ball : public GameObject {
public:
    Ball();
    Ball(float radius, const glm::vec2 &pos, const glm::vec2 &velocity, const Texture2D &sprite, bool isLight);

    glm::vec2 Move(float delta, unsigned int window_width, unsigned int window_height);
    void ReverseVelocity(const Direction &dir, const glm::vec2& diffVector);

    float GetRadius() const;
    Direction VectorDirection(const glm::vec2 &target) const;

private:
    float m_radius;
};