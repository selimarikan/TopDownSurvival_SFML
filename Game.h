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

    TextureManager m_TextureMgr;
    CharacterTopDown* m_pPlayer;

private:
	sf::RenderWindow m_Window;
	sf::View m_GameView;
	sf::View m_GUIView;

	void HandleEvents();
	void Render(float dt);
	void LoadTextures();

	std::list<ITile*> m_Tiles;

	std::filesystem::path m_AssetsDir;
};

