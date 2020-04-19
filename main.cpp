#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

#include "Extern/json.hpp"
#include "Game.h"
#include "Tile.h"

using json = nlohmann::json;

void LoadTextures()
{

}

int main()
{
    std::ifstream configFile("config.json");
    json config;
    configFile >> config;

    std::filesystem::path assetsPath = "Assets/";
	Game game(assetsPath);


	unsigned int tileSize = 32;
    unsigned int mapWidth = 1000;
    unsigned int mapHeight = 1000;
    
    Map map = Map(mapWidth, mapHeight, tileSize);
    
    std::vector<sf::Texture*> grassTextures;
    grassTextures.emplace_back(game.m_TextureMgr.GetTexture("grass01"));
    grassTextures.emplace_back(game.m_TextureMgr.GetTexture("grass02"));
    grassTextures.emplace_back(game.m_TextureMgr.GetTexture("grass03"));
    //grassTextures.emplace_back(game.m_TextureMgr.GetTexture("dirt"));
    map.AddTexture("grass", grassTextures);

    std::vector<sf::Texture*> wheatTextures;
    wheatTextures.emplace_back(game.m_TextureMgr.GetTexture("wheat_stage1"));
    wheatTextures.emplace_back(game.m_TextureMgr.GetTexture("wheat_stage2"));
    wheatTextures.emplace_back(game.m_TextureMgr.GetTexture("wheat_stage3"));
    wheatTextures.emplace_back(game.m_TextureMgr.GetTexture("wheat_stage4"));
    map.AddTexture("wheat", wheatTextures);

    std::vector<sf::Texture*> rockTextures;
    rockTextures.emplace_back(game.m_TextureMgr.GetTexture("rock"));
    rockTextures.emplace_back(game.m_TextureMgr.GetTexture("rock_moss"));
    map.AddTexture("rock", rockTextures);

    map.Build();

    //Animation grassAnim = Animation(0, 3, 2.0f);
    
    // Add tiles to the list so it gets rendered
    for (auto& tile: map.GetTiles())
    {
        game.AddObject(tile);
    }
    

    game.AddObject(game.m_pPlayer); //, "ThePlayer"
	game.Run();
	


	return 0;
}