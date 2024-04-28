#include "Ball.h"

Ball::Ball() : GameObject(), m_radius(12.5f)
{
}

Ball::Ball(float radius, const glm::vec2& pos, const glm::vec2& velocity, const Texture2D& sprite, bool isLight)
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, isLight, glm::vec3(1.0f), velocity),
      m_radius(radius)
{
}

glm::vec2 Ball::Move(float delta, unsigned int window_width, unsigned int window_height)
{
    m_position += m_velocity * delta;

    if (m_position.x <= 0.0f) {
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

/**
 * Reverses the velocity of the ball based on the given direction and adjusts
 * the position to resolve collision (penetration).
 * 
 * @param dir The direction of the collision.
 * @param diffVector The difference vector between the ball and the colliding object.
 */
void Ball::ReverseVelocity(const Direction& dir, const glm::vec2 &diffVector)
{
    if (dir == Direction::LEFT || dir == Direction::RIGHT) {
        m_velocity.x = -m_velocity.x;
        float penetration = m_radius - std::abs(diffVector.x);
        dir == Direction::LEFT ? m_position.x += penetration : m_position.x -= penetration;
    }
    else {
        m_velocity.y = -m_velocity.y;
        float penetration = m_radius - std::abs(diffVector.y);
        dir == Direction::DOWN ? m_position.y += penetration : m_position.y -= penetration;
    }
}

float Ball::GetRadius() const
{
    return m_radius;
}

/**
 * Calculates the direction of a vector relative to the compass directions.
 * 
 * @param target The target vector.
 * @return The direction of the vector.
 */
Direction Ball::VectorDirection(const glm::vec2 &target) const
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f), // up
        glm::vec2(1.0f, 0.0f), // right
        glm::vec2(0.0f, -1.0f), // down
        glm::vec2(-1.0f, 0.0f) // left
    };

    float max = 0.0f;
    unsigned int bestMatch = -1;

    for (unsigned int i = 0; i < 4; i++) {
        float dotProduct = glm::dot(glm::normalize(target), compass[i]);
        if (dotProduct > max) {
            max = dotProduct;
            bestMatch = i;
        }
    }

    return (Direction)bestMatch;
}
