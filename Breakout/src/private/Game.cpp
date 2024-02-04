#include "Game.h"

Game::Game(unsigned int width, unsigned int height)
    : m_width(width), m_height(height), m_state(GAME_ACTIVE), m_keys()
{
}

Game::~Game()
{
}

void Game::Init()
{
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
}
