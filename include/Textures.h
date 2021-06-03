#pragma once
#include <array>
#include <string>
#include <SFML/Graphics.hpp>

class Textures
{
public:
	const static auto MENU_TEXTURES = 6;
	const static auto BOARD_TEXTURES = 10;
	virtual ~Textures() = default;
	static Textures& instance();
	sf::Texture const& getBoardTexture(int index) const;
	sf::Texture const& getMenuTexture(int index) const;
private:
	std::array<sf::Texture, BOARD_TEXTURES>m_boardTextures;
	std::array<sf::Texture, MENU_TEXTURES>m_menuTextures;
	Textures();
	void loadBoardTextures();
	void loadMenuTextures();
};