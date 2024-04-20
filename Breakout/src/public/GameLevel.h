#pragma once
#include <vector>

#include "GameObject.h"
#include "SpriteRenderer.h"


class GameLevel {
public:
    GameLevel() { }

    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    void Draw(SpriteRenderer& renderer);

    bool IsCompleted();
    std::vector<GameObject>& getBricks();

private:
    std::vector<GameObject> m_bricks;

    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth,
        unsigned int levelHeight);
};