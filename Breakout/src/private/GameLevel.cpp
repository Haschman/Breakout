#include "GameLevel.h"

#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "ResourceManager.h"


void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    m_bricks.clear();
    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;

    // TODO: Check file for errors

    if (fstream) {
        while (std::getline(fstream, line)) {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
    for (GameObject& tile : m_bricks)
        if (!tile.isDestroyed())
            tile.Draw(renderer);
}

bool GameLevel::IsCompleted()
{
    for (GameObject& tile : m_bricks)
        if (!tile.isDestroyed())
            return false;
    return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth,
    unsigned int levelHeight)
{
    unsigned int height = tileData.size();
    // FIX: Only if all rows have the same number of columns
    unsigned int width = tileData[0].size();
    float unit_width = levelWidth / static_cast<float>(width);
    float unit_height = levelHeight / height;

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            if (tileData[y][x] != 0) {
                
                // TODO: Different types of bricks
                
                glm::vec3 color = glm::vec3(1.0f);
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);

                m_bricks.push_back(GameObject(pos, size,
                    ResourceManager::GetTexture("block"), color));
            }
        }
    }
}
