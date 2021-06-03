#include "Controller.h"
//------------------------------------------------------------
enum class buttons : int
{
	startButton = 2, exitButton = 4
};
//------------------------------------------------------------
Controller::Controller() : m_window(sf::RenderWindow(sf::VideoMode(m_WIDTH, m_HEIGHT), "Corona Runner by Idan Baumer and Shay Tobi")),
m_music(true)
{
	std::array <sf::Sprite, Textures::MENU_TEXTURES> m_sprites;
	loadSprites();
	mainMenu(false);
	while (m_window.isOpen())
	{
		run();
		mainMenu(true);
	}
}
//--------------------------------------------------------------------------
void Controller::loadSprites()
{
	for (int i = 0; i < Textures::instance().MENU_TEXTURES; i++)
		m_sprites[i].setTexture(Textures::instance().getMenuTexture(i));
	m_sprites[1].setPosition((float)m_WIDTH / 2 - m_sprites[1].getGlobalBounds().width / 2, 110.f + 20.f);
	for (size_t i = 2; i < m_sprites.size() - 1; i += 2)
	{
		m_sprites[i].setPosition((float)m_WIDTH / 2 - m_sprites[i].getGlobalBounds().width / 2, 120.f + i * 90.f);
		m_sprites[i + 1].setPosition((float)m_WIDTH / 2 - m_sprites[i + 1].getGlobalBounds().width / 2,
			120.f + i * 90.f);
	}
}
//----------------------------------------------------------------------------
sf::Texture const& Controller::getTexture(int index) const
{
	return Textures::instance().getMenuTexture(index);
}
//----------------------------------------------------------------------------
void Controller::mainMenu(bool gameOver)
{
	auto option = -1, candidate = (int)buttons::startButton;
	Music::instance().pauseBackgroundMusic();
	if (gameOver)
		Music::instance().startGameOverSound();
	while (m_window.isOpen() && option == -1)
	{
		m_window.clear();
		m_window.draw(m_sprites[0]);
		if (gameOver)
			m_window.draw(m_sprites[1]);
		for (int i = 2; i < m_sprites.size() - 1; i += 2)
			m_window.draw(m_sprites[(i == candidate) ? i + 1 : i]);
		m_window.display();
		if (auto event = sf::Event{}; m_window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				Music::instance().startClickSound();
				m_window.close();
				break;
			case sf::Event::MouseMoved:
			{
				auto location = m_window.mapPixelToCoords(
					{ event.mouseMove.x, event.mouseMove.y });
				checkIfcontains(location, candidate);
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				auto location = m_window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });

				checkIfcontains(location, option);
				Music::instance().startClickSound();
				break;
			}
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Key::Up:
					Music::instance().startClickSound();
					candidate = (int)buttons::startButton;
					break;
				case sf::Keyboard::Key::Down:
					Music::instance().startClickSound();
					candidate = (candidate == (int)buttons::startButton) ? (int)buttons::exitButton :
						(int)buttons::startButton;
					break;
				case sf::Keyboard::Key::Enter:
					Music::instance().startClickSound();
					option = candidate;
					break;
				}
				break;
			}
		}
	}
	if (option == (int)buttons::exitButton)
		m_window.close();
}
//-------------------------------------------------------------------------------------
void Controller::checkIfcontains(Location location, int& wantedValue)
{
	for (int i = 2; i < m_sprites.size(); i += 2)
		if (m_sprites[i].getGlobalBounds().contains(location))
		{
			wantedValue = i;
			Music::instance().startClickSound();
			break;
		}
}
//------------------------------------------------------------------------------------
void Controller::run()
{
	Board board;//store board
	Music::instance().pauseGameOverSound();
	Music::instance().startBackgroundMusic();
	auto clock = sf::Clock();
	m_window.setFramerateLimit(60);

	auto view = sf::View(sf::FloatRect(0, 0, m_WIDTH, m_HEIGHT));
	view.setCenter(getViewCenter(board));
	m_window.setView(view);

	while (m_window.isOpen())
	{
		const auto deltaTime = clock.restart();
		board.moveObject(objectsType::enemy, deltaTime);

		for (auto event = sf::Event{}; m_window.pollEvent(event);)
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::M)
				{
					m_music ? Music::instance().pauseBackgroundMusic() : Music::instance().startBackgroundMusic();
					m_music = !m_music;
				}
				else
				{
					board.moveObject(objectsType::player, deltaTime, event.key.code);
					view.setCenter(getViewCenter(board));
					m_window.setView(view);
				}
				break;
			}
		}
		if (board.gameOver())
			break;
		board.draw_objects(m_window);
	}
	m_window.setView(m_window.getDefaultView());//set current view
}
//-----------------------------------------------------------------------------------------
Location Controller::getViewCenter(const Board& board) const
{
	auto rec = sf::RectangleShape(Location((float)m_WIDTH, (float)m_HEIGHT));
	for (int i = 0; i * m_HEIGHT < board.getBoardHeight(); i++)
		for (int j = 0; j * m_WIDTH < board.getBoardWidth(); j++)
		{
			rec.setPosition(Location((float)j * m_WIDTH, (float)i * m_HEIGHT));

			if (rec.getGlobalBounds().contains(board.getPlayerLocation()))
				return Location((float)j * m_WIDTH + m_WIDTH / 2, (float)i * m_HEIGHT + m_HEIGHT / 2);
		}
	return Location(m_WIDTH / 2, m_HEIGHT / 2);
}