#include "Textures.h"
//-----Texture Constructor-------------------------------------------------------------------------------
Textures::Textures()
{
	loadBoardTextures();
	loadMenuTextures();
}
//-----------------------------------------------------------------------------------------------
void Textures::loadBoardTextures()
{
	std::array <std::string, BOARD_TEXTURES> texturesName =
	{
		"Background", "Ladder", "Wall", "Rope", "Vaccine",
		"Player", "Treasure", "LeftRightEnemy", "RandomEnemy",
		"SmartEnemy"
	};
	for (int i = 0; i < texturesName.size(); i++)
		m_boardTextures[i].loadFromFile(texturesName[i] + ".png");
	m_boardTextures[0].setRepeated(true);
}
//-----------------------------------------------------------------------------------------------
void Textures::loadMenuTextures()
{
	std::array <std::string, MENU_TEXTURES> texturesName =
	{ "Menu", "GameOver", "BlackStart",  "RedStart", "BlackExit", "RedExit" };

	for (int i = 0; i < texturesName.size(); i++)
		m_menuTextures[i].loadFromFile(texturesName[i] + ".png");
}
//-----------------------------------------------------------------------------------------------
Textures& Textures::instance()
{
	static Textures texture;
	return texture;
}
//-----------------------------------------------------------------------------------------------
sf::Texture const& Textures::getBoardTexture(int index) const
{
	return m_boardTextures[index];
}
//-----------------------------------------------------------------------------------------------
sf::Texture const& Textures::getMenuTexture(int index) const
{
	return m_menuTextures[index];//returns texture of menu
}