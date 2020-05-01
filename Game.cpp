#include "Game.h"
#include "AnimationHandler.h"
#include <SFML/System.hpp>

#define TILE_SIZE 32


// TODO: Create map editor from txt file
// TODO: Move map/view when close to the edges
// TODO: Create "options" class
Game::Game(const std::filesystem::path& assetsDir): m_AssetsDir(assetsDir)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    m_Window.create(sf::VideoMode(800, 600), "TDDEF", sf::Style::Default, settings);
    m_Window.setVerticalSyncEnabled(false);
    m_Window.setFramerateLimit(MAX_FRAMES);
    m_GameView.setSize(sf::Vector2f(800, 600));

    LoadTextures();

    Map map = Map(m_MapWidth, m_MapHeight, m_TileSize);
    std::vector<sf::Texture*> grassTextures;
    grassTextures.emplace_back(m_TextureMgr.GetTexture("grass01"));
    grassTextures.emplace_back(m_TextureMgr.GetTexture("grass02"));
    grassTextures.emplace_back(m_TextureMgr.GetTexture("grass03"));
    //grassTextures.emplace_back(game.m_TextureMgr.GetTexture("dirt"));
    map.AddTexture("grass", grassTextures);
    //Animation grassAnim = Animation(0, 3, 2.0f);

    

    std::vector<sf::Texture*> wheatTextures;
    wheatTextures.emplace_back(m_TextureMgr.GetTexture("wheat_stage1"));
    wheatTextures.emplace_back(m_TextureMgr.GetTexture("wheat_stage2"));
    wheatTextures.emplace_back(m_TextureMgr.GetTexture("wheat_stage3"));
    wheatTextures.emplace_back(m_TextureMgr.GetTexture("wheat_stage4"));
    map.AddTexture("wheat", wheatTextures);

    std::vector<sf::Texture*> rockTextures;
    rockTextures.emplace_back(m_TextureMgr.GetTexture("rock"));
    rockTextures.emplace_back(m_TextureMgr.GetTexture("rock_moss"));
    map.AddTexture("rock", rockTextures);

    map.Build();

    // Add tiles to the list so it gets rendered
    for (auto& tile: map.GetTiles())
    {
        AddObject(tile);
    }
    


    // m_pPlayer = new Character(sf::Vector2f(32.0f, 32.0f), 
    //     m_TextureMgr.GetTexture("c1_stand_left01"), 
    //     m_TextureMgr.GetTexture("c1_stand_up01"), 
    //     m_TextureMgr.GetTexture("c1_stand_right01"), 
    //     m_TextureMgr.GetTexture("c1_stand_down01"),
    //     m_TextureMgr.GetTexture("c1_move_left01"),
    //     m_TextureMgr.GetTexture("c1_move_left02"),
    //     m_TextureMgr.GetTexture("c1_move_up01"),
    //     m_TextureMgr.GetTexture("c1_move_up02"),
    //     m_TextureMgr.GetTexture("c1_move_right01"),
    //     m_TextureMgr.GetTexture("c1_move_right02"),
    //     m_TextureMgr.GetTexture("c1_move_down01"),
    //     m_TextureMgr.GetTexture("c1_move_down02"), 255);
    m_pPlayer = new CharacterTopDown(sf::Vector2f(32.0f, 32.0f), m_TextureMgr.GetTexture("survivor1_stand"), 255);
    m_pPlayer->SetPosition(sf::Vector2f(150.0f, 150.0f));
    // Animation standAnim = Animation(0, 3, 1.0f);
    // Animation leftAnim = Animation(0, 1, 0.5f);
    // Animation upAnim = Animation(0, 1, 0.5f);
    // Animation rightAnim = Animation(0, 1, 0.5f);
    // Animation downAnim = Animation(0, 1, 0.5f);
    // m_pPlayer->AddAnim(standAnim);
    // m_pPlayer->AddAnim(leftAnim);
    // m_pPlayer->AddAnim(upAnim);
    // m_pPlayer->AddAnim(rightAnim);
    // m_pPlayer->AddAnim(downAnim);

    AddObject(m_pPlayer); //, "ThePlayer"

}

void Game::Run()
{
    sf::Clock clock;

    // Sort sprites once by their ZLevel.
    //   This may be needed per render or maybe per level load
    m_Tiles.sort([](ITile* tile1, ITile* tile2) { return tile1->ZLevel < tile2->ZLevel; });

    while (m_Window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        HandleEvents();

        Render(dt);
        //std::cout << dt << "\n"; //DBG
    }
}

void Game::HandleEvents()
{
    sf::Event event;

    while (m_Window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                m_Window.close();
                break;
            }
            case sf::Event::Resized:
            {
                m_GameView.setSize(event.size.width, event.size.height);
                m_GameView.setCenter(event.size.width / 2.0f, event.size.height / 2.0f);
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    m_Window.close();
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    const sf::Vector2f centerPt = m_GameView.getCenter();
                    m_GameView.setCenter(centerPt.x + TILE_SIZE, centerPt.y);
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    const sf::Vector2f centerPt = m_GameView.getCenter();
                    m_GameView.setCenter(centerPt.x - TILE_SIZE, centerPt.y);
                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    const sf::Vector2f centerPt = m_GameView.getCenter();
                    m_GameView.setCenter(centerPt.x, centerPt.y - TILE_SIZE);
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    const sf::Vector2f centerPt = m_GameView.getCenter();
                    m_GameView.setCenter(centerPt.x, centerPt.y + TILE_SIZE);
                    
                }
                else if (event.key.code == sf::Keyboard::W)
                {
                    // m_pPlayer->Turn(MapDirection::UP);
                    m_pPlayer->Move(MapDirection::UP);
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    // m_pPlayer->Turn(MapDirection::DOWN);
                    m_pPlayer->Move(MapDirection::DOWN);
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    // m_pPlayer->Turn(MapDirection::LEFT);
                    m_pPlayer->Move(MapDirection::LEFT);
                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    // m_pPlayer->Turn(MapDirection::RIGHT);
                    m_pPlayer->Move(MapDirection::RIGHT);
                }
                break;
            }
            // TL origin, gives coordinates in screen pixels, non-normalized
            case sf::Event::MouseMoved:
            {
                // Get the positions and calc the difference vector
                auto mousePos = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
                auto playerPos = m_pPlayer->GetPosition();
                auto delta = mousePos - playerPos;
                
                // std::cout << "Mx: " << event.mouseMove.x << " My: " << event.mouseMove.y << std::endl;
                // std::cout << "PlayerX: " << playerPos.x << " PlayerY: " << playerPos.y << std::endl;
                float rotRad = atan2f(delta.y, delta.x);
                float rotDeg = (rotRad * 180.0f) / 3.141592f;

                // std::cout << "rotRad: " << rotRad << " rotDeg: " << rotDeg << std::endl;

                m_pPlayer->SetRotation(rotDeg);
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // std::vector<sf::Texture*> textures;
                    // textures.emplace_back(m_TextureMgr.GetTexture("dot"));
                    // Tile tile = Tile(sf::Vector2f(16, 16), textures, 255);
                    // m_Tiles.emplace_back(tile);
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    
                }
                else
                {

                }
                break;
            }
            /*case sf::Event::MouseWheelScrolled:
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    float delta = event.mouseWheelScroll.delta;
                    sf::FloatRect view = m_GameView.getViewport();
                    view.top
                    m_GameView.setViewport()
                }
                break;
            }*/
            default:
                break;
        }
    }
}

void Game::Render(float dt)
{
    m_Window.setView(m_GameView);
    m_Window.clear();

    // Draw all objects
    for (const auto val : m_Tiles)
    {
        m_Window.draw(*val->Get(dt));
    }

    m_Window.display();
}

// Checks if the texture is a strip by checking the name, returns the strip length for slice
bool IsTextureStrip(const std::filesystem::path& texturePath, int& splitLen)
{
    auto pathVec = TDDEF::Utils::Split(texturePath.filename().stem().string(), '_');
    std::string stripStr = "strip";
    size_t found = pathVec.back().find(stripStr);
    return found != std::string::npos;
}

void Game::LoadTextures()
{
    std::cout << "Loading textures from " << m_AssetsDir << "...\n";

    // Load characters
    // TODO: Test tile loading
    std::filesystem::path charDir = m_AssetsDir / "characters";
    for (const auto& entry : std::filesystem::directory_iterator(charDir))
    {
        std::filesystem::path path = entry.path();
        
        int splitLen = 0;
        if (IsTextureStrip(path, splitLen))
        {
            m_TextureMgr.LoadSheet(path.filename().stem().string(), path.string(), splitLen, splitLen, 64, 64);
        }
        else
        {
            m_TextureMgr.LoadTexture(path.filename().stem().string(), path.string());
        }
            
        std::cout << "Loading texture: " << path.filename().stem() << std::endl; //DBG
    }

    // Load all the tiles
    // TODO: Add tile support
    std::filesystem::path tilesDir = m_AssetsDir / "tiles/";
    for (const auto& entry : std::filesystem::directory_iterator(tilesDir))
    {
        std::filesystem::path path = entry.path();
        m_TextureMgr.LoadTexture(path.filename().stem().string(), path.string());
        std::cout << "Loading texture: " << path.filename().stem() << std::endl; //DBG
    }

    std::cout << "Loaded textures.\n";
}

bool Game::AddObject(ITile* pObj)
{
    m_Tiles.emplace_back(pObj);
    return true;
}

// TODO: Fix this
bool Game::RemoveObject(int id)
{
    //m_DrawablesMap.remove()
    return true;
}
