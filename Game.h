#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <list>
#include <memory>

// #include "Character.h"
#include "CharacterTopDown.h"
#include "ITile.h"
#include "Map.h"
#include "TextureManager.h"
#include "Utils.h"

constexpr auto MAX_FRAMES = 60;

class Game
{
public:

	Game(const std::filesystem::path& assetsDir);
    bool AddObject(ITile* pObj);
	bool RemoveObject(int id);
	void Run();

    CharacterTopDown* m_pPlayer;

private:
	sf::RenderWindow m_Window;
	sf::View m_GameView;
	sf::View m_GUIView;

	void HandleEvents();
	void Render(float dt);
	void LoadTextures();

    TextureManager m_TextureMgr;

	std::list<ITile*> m_Tiles;

    unsigned int m_TileSize = 32;
    unsigned int m_MapWidth = 1000;
    unsigned int m_MapHeight = 1000;
	std::filesystem::path m_AssetsDir;
};

