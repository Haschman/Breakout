#include "Game.h"
#include "ResourceManager.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


// TODO: Move these to a config file
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 12.5f;


Game::Game(unsigned int width, unsigned int height)
    : m_width(width), m_height(height), m_state(GAME_ACTIVE), m_keys()
{
}

Game::~Game()
{
    delete m_spriteRenderer;
}

void Game::Init()
{
    ResourceManager::LoadShader(
        "src/shaders/shader.vert",
        "src/shaders/shader.frag",
        nullptr,
        "sprite"
    );
    glm::mat4 projection = glm::ortho(
        0.0f,
        static_cast<float>(m_width),
        static_cast<float>(m_height),
        0.0f,
        -1.0f,
        1.0f
    );
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);

    m_spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    ResourceManager::LoadTexture("resources/block.png", false, "block");

    GameLevel one;
    one.Load("resources/levels/1.lvl", m_width, m_height / 2);
    m_levels.push_back(one);
    m_currentLevel = 0;

    ResourceManager::LoadTexture("resources/white_ball.png", true, "white_ball");

    glm::vec2 ballPos = glm::vec2((m_width / 2) - (BALL_RADIUS), m_height - BALL_RADIUS * 2);
    m_ball = new Ball(
        BALL_RADIUS,
        ballPos,
        INITIAL_BALL_VELOCITY,
        ResourceManager::GetTexture("white_ball")
    );
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
    m_ball->Move(dt, m_width, m_height);
}

void Game::Render()
{
    if (m_state == GAME_ACTIVE) {
        m_levels[m_currentLevel].Draw(*m_spriteRenderer);
        m_ball->Draw(*m_spriteRenderer);
    }
}
