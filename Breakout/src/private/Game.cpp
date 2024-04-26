#include "Game.h"
#include "ResourceManager.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


// TODO: Move these to a config file
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 12.5f;


Game::Game(unsigned int width, unsigned int height)
    : m_width(width), m_height(height), m_state(GAME_ACTIVE), m_keys(), m_ball(nullptr),
    m_currentLevel(0), m_spriteRenderer(nullptr)
{
}

Game::~Game()
{
    delete m_spriteRenderer;
    delete m_ball;
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
    DoCollisions();
    m_ball->Move(dt, m_width, m_height);
}

void Game::Render()
{
    if (m_state == GAME_ACTIVE) {
        m_levels[m_currentLevel].Draw(*m_spriteRenderer);
        m_ball->Draw(*m_spriteRenderer);
    }
}

/**
 * @brief Check if the ball has collided with a GameObject of type AABB.
 * 
 * First, calculate the AABB's center and half extents.
 * Then calculate the difference between the ball's center and the AABB's
 * center.
 * Next, clamp the difference vector to the AABB's half extents.
 * Calculate the closest point on the AABB to the ball.
 * And finally, calculate the difference between the closest point and the
 * ball's center.
 * 
 * @param aabbObj The GameObject to check for collision with.
 * @return A collision tuple containing a boolean indicating if a collision
 * has occurred, the direction of the collision, and the difference vector.
 */
Collision Game::CheckBallCollision(GameObject& aabbObj)
{
    glm::vec2 ballCenter(m_ball->getPosition() + m_ball->getRadius());
    glm::vec2 aabbHalfExtents(aabbObj.getSize() / 2.0f);
    glm::vec2 aabbCenter(aabbObj.getPosition() + aabbHalfExtents);

    glm::vec2 difference(ballCenter - aabbCenter);
    glm::vec2 clamped(
        glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents)
    );
    glm::vec2 closest(aabbCenter + clamped);

    difference = closest - ballCenter;
    
    if (glm::length(difference) < m_ball->getRadius())
        return std::make_tuple(true, m_ball->VectorDirection(difference), difference);
    return std::make_tuple(false, UP, glm::vec2(0.0f));
}

/**
 * @brief Check for collisions between the ball and the bricks.
 * 
 * For each brick in the current level, check if the ball has collided with
 * the brick. If the ball has collided with the brick, destroy the brick. Then
 * reverse the ball's velocity based on the direction of the collision and the
 * difference vector (penetration of the ball).
 */
void Game::DoCollisions()
{
    for (GameObject& brick : m_levels[m_currentLevel].getBricks()) {
        if (!brick.isDestroyed()) {
            Collision collision = CheckBallCollision(brick);
            if (std::get<bool>(collision)) {
                brick.Destroy();

                Direction dir = std::get<Direction>(collision);
                glm::vec2 diffVector = std::get<glm::vec2>(collision);
                m_ball->ReverseVelocity(dir, diffVector);
            }
        }
    }
}
