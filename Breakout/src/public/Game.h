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

    void ProcessInput(float dt);
    void Update(float dt);
    void Render();

    bool m_keys[1024];

private:
    Collision CheckBallCollision(GameObject& aabbObj, Ball *ball);
    void DoCollisions();

    GameState m_state;
    unsigned int m_width, m_height;

    std::vector<GameLevel> m_levels;

    std::vector<std::unique_ptr<Ball>> m_balls;
    SpriteRenderer* m_spriteRenderer;
};
