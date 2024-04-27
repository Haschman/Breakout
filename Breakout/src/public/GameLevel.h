#pragma once
#include <vector>

#include "GameObject.h"
#include "SpriteRenderer.h"


class GameLevel {
public:
    GameLevel() { }

    void Init(float numOfLines, float numOfBricksPerLine, float width, float height);
    void Draw(SpriteRenderer& renderer, const glm::vec3& color);

    bool IsCompleted();
    std::vector<GameObject>& getBricks();

private:
    std::vector<GameObject> m_bricks;
};