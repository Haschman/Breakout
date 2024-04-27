#include "GameObject.h"

GameObject::GameObject()
    : m_position(0.0f, 0.0f),
      m_size(1.0f, 1.0f),
      m_sprite(),
      m_isLight(false),
      m_color(1.0f),
      m_velocity(0.0f, 0.0f)
{
}

GameObject::GameObject(
    glm::vec2 pos,
    glm::vec2 size,
    Texture2D sprite,
    bool isLight,
    glm::vec3 color,
    glm::vec2 velocity
)
    : m_position(pos),
      m_size(size),
      m_sprite(sprite),
      m_isLight(isLight),
      m_color(color),
      m_velocity(velocity)
{
}

void GameObject::Draw(SpriteRenderer& renderer, const glm::vec3 &color)
{
    m_isLight ?
        renderer.DrawSprite(m_sprite, m_position, m_size, m_rotation, color) :
        renderer.DrawSprite(m_sprite, m_position, m_size, m_rotation, glm::vec3(1.0f - color));
}

void GameObject::Destroy()
{
    m_isLight = !m_isLight;
}

bool GameObject::isLight() const
{
    return m_isLight;
}

glm::vec2 GameObject::getPosition() const
{
    return m_position;
}

glm::vec2 GameObject::getSize() const
{
    return m_size;
}
