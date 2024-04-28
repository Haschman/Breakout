#pragma once

#include <vector>
#include <memory>

#include "GameLevel.h"
#include "Ball.h"
#include "SpriteRenderer.h"


// Current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_END
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

class Game {
public:
    Game(unsigned int width, unsigned int height);
    ~Game();

    void Init();
    void AddBall(bool isWhite);
    void RemoveBall(bool isWhite);

    void ProcessInput(float dt);
    void Update(float dt);
    void Render(const glm::vec3 &color);

private:
    Collision CheckBallCollision(const GameObject& aabbObj, const Ball &ball);
    void DoCollisions();

    GameState m_state;
    unsigned int m_width, m_height;

    std::vector<GameLevel> m_levels;

    std::vector<std::unique_ptr<Ball>> m_balls;
    std::unique_ptr<SpriteRenderer> m_spriteRenderer;
};
