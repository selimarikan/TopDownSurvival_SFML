#include "TextureManager.h"

void TextureManager::LoadTexture(const std::string &name, const std::string &filename)
{
    sf::Texture *pTex = new sf::Texture();
    pTex->loadFromFile(filename);

    m_Textures[name] = pTex;
}

void TextureManager::LoadSheet(const std::string &name, const std::string &filename, int n_cols, int sprite_count, float single_width, float single_height)
{
    try
    {
        for (size_t iTexture = 0; iTexture < sprite_count; iTexture++)
        {
            sf::Texture *pTex = new sf::Texture();
            // Calculate top left of the texture, width and height are the same for all
            int left = iTexture * single_width;
            int top = iTexture * single_height;
            pTex->loadFromFile(filename, sf::IntRect(left, top, single_width, single_height));

            // Pattern is name_0, name_1, etc.
            m_Textures[name + "_" + std::to_string(iTexture)] = pTex;
        }
    }
    catch (const std::exception &e)
    {
        // TODO: Handle possible memory leaks
        std::cerr << e.what() << '\n';
    }
}

sf::Texture *TextureManager::GetTexture(const std::string &name)
{
    return m_Textures.at(name);
}
