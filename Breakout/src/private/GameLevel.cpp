#include "GameLevel.h"

#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "ResourceManager.h"


void GameLevel::Init(float numOfLines, float numOfBricksPerLine, float width, float height)
{
    m_bricks.clear();

    float brickWidht = width / numOfBricksPerLine;
    float brickHeight = height / 2 / numOfLines;

    for (unsigned int line = 0; line < numOfLines; line++) {
        for (unsigned int brick = 0; brick < numOfBricksPerLine; brick++) {
            glm::vec3 lightColor = glm::vec3(1.0f);
            glm::vec2 lightPos(brickWidht * brick, brickHeight * line);
            glm::vec2 darkPos(brickWidht * brick, brickHeight * line + numOfLines * brickHeight);
            glm::vec2 size(brickWidht, brickHeight);

            m_bricks.emplace_back(lightPos, size, ResourceManager::GetTexture("block"), true, lightColor);
            m_bricks.emplace_back(darkPos, size, ResourceManager::GetTexture("block"), false, lightColor);
        }
    }
}

void GameLevel::Draw(SpriteRenderer& renderer, const glm::vec3 &color)
{
    for (GameObject& tile : m_bricks)
        tile.Draw(renderer, color);
}

bool GameLevel::IsCompleted()
{
    return false;
}

std::vector<GameObject>& GameLevel::GetBricks()
{
    return m_bricks;
}
