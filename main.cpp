#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

#include "Extern/json.hpp"
#include "Game.h"
#include "Tile.h"

using json = nlohmann::json;

int main()
{
    std::ifstream configFile("config.json");
    json config;
    configFile >> config;

    std::filesystem::path assetsPath = "Assets/";
    Game game(assetsPath);

    game.Run();

    return 0;
}