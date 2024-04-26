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
    Ball(float radius, glm::vec2 pos, glm::vec2 velocity, Texture2D sprite);

    glm::vec2 Move(float delta, unsigned int window_width, unsigned int window_height);
    void Reset(const glm::vec2 &position, const glm::vec2 &velocity);
    void ReverseVelocity(const Direction &dir, const glm::vec2& diffVector);

    float getRadius() const;
    Direction VectorDirection(const glm::vec2 &target) const;

private:
    float m_radius;
};