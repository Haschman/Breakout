#include "Game.h"
#include "ResourceManager.h"
#include "white_ball.h"
#include "block_white.h"

#include <time.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


// TODO: Move these to a config file
const float BALL_RADIUS = 12.5f;


Game::Game(unsigned int width, unsigned int height)
    : m_width(width), m_height(height), m_state(GAME_ACTIVE)
{
}

Game::~Game()
{
}

void Game::Init()
{
    ResourceManager::LoadShader("MainShader");
    glm::mat4 projection = glm::ortho(
        0.0f,
        static_cast<float>(m_width),
        static_cast<float>(m_height),
        0.0f,
        -1.0f,
        1.0f
    );
    ResourceManager::GetShader("MainShader").Use().SetInteger("image", 0);
    ResourceManager::GetShader("MainShader").Use().SetMatrix4("projection", projection);

    m_spriteRenderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("MainShader"));

    ResourceManager::LoadTextureFromHeader(block_white_png, block_white_png_len, false, "block");

    GameLevel one;
    one.Init(10.0f, 15.0f, static_cast<float>(m_width), static_cast<float>(m_height));
    m_levels.push_back(one);

    ResourceManager::LoadTextureFromHeader(white_ball_png, white_ball_png_len, true, "white_ball");
    std::srand(time(0));
}

void Game::AddBall(bool isWhite) {
    float posY = isWhite ? m_height - BALL_RADIUS * 2.0f : BALL_RADIUS * 2.0f;
    float velocityX = std::rand() % 2 ? 200.0f : -200.0f;
    float velocityY = isWhite ? -350.0f : 350.0f;

    m_balls.push_back(std::make_unique<Ball>(
        BALL_RADIUS,
        glm::vec2(
            (float)(rand() % (m_width - (int)BALL_RADIUS - (int)BALL_RADIUS + 1)) + (int)BALL_RADIUS,
            posY
        ),
        glm::vec2(velocityX, velocityY),
        ResourceManager::GetTexture("white_ball"),
        isWhite
    ));
}

void Game::RemoveBall(bool isWhite) {
    for (auto it = m_balls.begin(); it != m_balls.end(); it++) {
        if ((*it)->IsLight() == isWhite) {
            m_balls.erase(it);
            break;
        }
    }
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
    DoCollisions();
    for (auto& ball : m_balls)
        ball->Move(dt, m_width, m_height);
}

void Game::Render(const glm::vec3 &color)
{
    if (m_state == GAME_ACTIVE) {
        m_levels[0].Draw(*m_spriteRenderer, color);
        for (auto& ball : m_balls)
            ball->Draw(*m_spriteRenderer, color);
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
Collision Game::CheckBallCollision(const GameObject& aabbObj, const Ball &ball)
{
    if (aabbObj.IsLight() + ball.IsLight() == 1)
        return std::make_tuple(false, UP, glm::vec2(0.0f));

    glm::vec2 ballCenter(ball.GetPosition() + ball.GetRadius());
    glm::vec2 aabbHalfExtents(aabbObj.GetSize() / 2.0f);
    glm::vec2 aabbCenter(aabbObj.GetPosition() + aabbHalfExtents);

    glm::vec2 difference(ballCenter - aabbCenter);
    glm::vec2 clamped(
        glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents)
    );
    glm::vec2 closest(aabbCenter + clamped);

    difference = closest - ballCenter;
    
    if (glm::length(difference) < ball.GetRadius())
        return std::make_tuple(true, ball.VectorDirection(difference), difference);
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
    for (GameObject& brick : m_levels[0].GetBricks()) {
        for (auto& ball : m_balls) {
            Collision collision = CheckBallCollision(brick, *ball);
            if (std::get<bool>(collision)) {
                brick.Destroy();
        
                Direction dir = std::get<Direction>(collision);
                glm::vec2 diffVector = std::get<glm::vec2>(collision);
                ball->ReverseVelocity(dir, diffVector);
            }
        }
    }
}
