#pragma once

#include <vector>

#include "GameLevel.h"


// Current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_END
};

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
    GameState m_state;
    unsigned int m_width, m_height;

    std::vector<GameLevel> m_levels;
    unsigned int m_currentLevel;
};
