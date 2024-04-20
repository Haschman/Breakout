#include "Ball.h"

Ball::Ball() : GameObject(), m_radius(12.5f)
{
}

Ball::Ball(float radius, glm::vec2 pos, glm::vec2 velocity, Texture2D sprite)
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(1.0f), velocity),
      m_radius(radius)
{
}

glm::vec2 Ball::Move(float delta, unsigned int window_width, unsigned int window_height)
{
    m_position += m_velocity * delta;

    if (m_position.x <= 0.0f) { // hit left side of window
        m_velocity.x = -m_velocity.x;
        m_position.x = 0.0f;
    }
    else if (m_position.x + m_size.x >= window_width) {
        m_velocity.x = -m_velocity.x;
        m_position.x = window_width - m_size.x;
    }
    if (m_position.y <= 0.0f) {
        m_velocity.y = -m_velocity.y;
        m_position.y = 0.0f;
    }
    else if (m_position.y + m_size.y >= window_height) {
        m_velocity.y = -m_velocity.y;
        m_position.y = window_height - m_size.y;
    }
    return m_position;
}

void Ball::Reset(glm::vec2 position, glm::vec2 velocity)
{
    m_position = position;
    m_velocity = velocity;
}

float Ball::getRadius() const
{
    return m_radius;
}
