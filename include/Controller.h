#pragma once
#include "Board.h"
#include "Music.h"

class Controller
{
public:
	Controller();
protected:

private:
	std::array <sf::Sprite, Textures::MENU_TEXTURES> m_sprites;
	sf::RenderWindow m_window;
	bool m_music;
	const static unsigned int m_WIDTH = 1280;
	const static unsigned int m_HEIGHT = 720;
	void mainMenu(bool gameOver);
	void loadSprites();
	sf::Texture const& getTexture(int index) const;
	void checkIfcontains(Location location, int& wantedValue);
	void run();
	Location getViewCenter(const Board& board) const;
};