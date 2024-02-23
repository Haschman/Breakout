#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


SpriteRenderer* spriteRenderer;

Game::Game(unsigned int width, unsigned int height)
    : m_width(width), m_height(height), m_state(GAME_ACTIVE), m_keys()
{
}

Game::~Game()
{
    delete spriteRenderer;
}

void Game::Init()
{
    ResourceManager::LoadShader("src/shaders/shader.vert", "src/shaders/shader.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_width),
        static_cast<float>(m_height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);

    spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    ResourceManager::LoadTexture("resources/flower.png", true, "flower");
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
    spriteRenderer->DrawSprite(ResourceManager::GetTexture("flower"),
        glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f,
        glm::vec3(1.0f, 1.0f, 1.0f));
}
