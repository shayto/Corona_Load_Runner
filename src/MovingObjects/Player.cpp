#include "MovingObjects/Player/Player.h"
#include "Board.h"
//-----------------------------------------------------------------------------
Player::Player(const sf::Texture& texture, Location location, int lives, int points, int level)
	: MovingObjects(texture, location), m_lives(lives), m_points(points), m_level(level), m_initialLocation(location),
	m_initialPoints(points), m_killed(false)
{
	initilizeFontText();
	Location m_previousLocation = m_initialLocation;
};
//-----------------------------------------------------------------------------
void Player::initilizeFontText()
{
	m_font.loadFromFile("C:/Windows/Fonts/SHOWG.TTF");
	for (int i = 0; i < m_texts.size(); i++)
	{
		m_texts[i].setFont(m_font);
		m_texts[i].setFillColor(sf::Color::Red);
	}
	m_texts[0].setString("Lives:" + std::to_string(m_lives));
	m_texts[1].setString("Points:" + std::to_string(m_points));
	m_texts[2].setString("Level: " + std::to_string(m_level));
}
//-----------------------------------------------------------------------------
int Player::getLives()const 
{ 
	return m_lives;
}
//-----------------------------------------------------------------------------
int Player::getLevel()const
{
	return m_level;
}
//-----------------------------------------------------------------------------
void Player::moreLives() 
{
	m_lives++;
}
//-----------------------------------------------------------------------------
bool Player::isDead() const
{
	return m_killed;
}
//-----------------------------------------------------------------------------
void Player::reborn()
{
	m_killed = false;
}
//-----------------------------------------------------------------------------
void Player::lessLives()
{
	m_lives--;
	m_killed = true;
	m_texts[0].setString("Lives:" + std::to_string(m_lives));
	setSpritePosition(m_initialLocation);
	m_points = m_initialPoints;
	m_texts[1].setString("Points:" + std::to_string(m_points));
}
//-----------------------------------------------------------------------------
int Player::getPoints()const 
{
	return m_points; 
}
//-----------------------------------------------------------------------------
void Player::draw(sf::RenderWindow& window) 
{
	window.draw(getSprite());
	for (int i = 0; i < m_texts.size(); i++)
	{
		m_texts[i].setPosition(100.f + window.getView().getCenter().x - window.getSize().x / 2 + 200.f * (float)i, window.getView().getCenter().y + window.getSize().y / 2.f - 40.f);
		window.draw(m_texts[i]);
	}
}
//-----------------------------------------------------------------------------
void Player::move(sf::Time DeltaTime, Board& board, const sf::Keyboard::Key& key)
{
	Location nextMove;
	switch (key) {
	case sf::Keyboard::Key::Left:
	{
		nextMove = getDirection(Direction::LEFT);
		break;
	}
	case sf::Keyboard::Key::Right:
	{
		nextMove = getDirection(Direction::RIGHT);
		break;
	}
	case sf::Keyboard::Key::Up:
	{
		nextMove = getDirection(Direction::UP);
		break;
	}
	case sf::Keyboard::Key::Down:
	{
		nextMove = getDirection(Direction::DOWN);
		break;
	}
	case sf::Keyboard::Key::Z:
	{
		digWall(board, Direction::LEFT);
		break;
	}
	case sf::Keyboard::Key::X:
	{
		digWall(board, Direction::RIGHT);
		break;
	}
	default:
	{
		nextMove = getDirection(Direction::DEFAULT);
		break;
	}
	}
	updatePrevPosition();
	moveSpritePosition(nextMove * DeltaTime.asSeconds() * SPEED_PER_SECONDS);
	validMove(board);

}
//-----------------------------------------------------------------------------
void Player::digWall(Board& board, MovingObjects::Direction direction)
{
	moveSpritePosition(getDirection(direction) * (STATIC_SPRITE_SIZE + (STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE)));
	moveSpritePosition(getDirection(Direction::DOWN) * (DYNAMIC_SPRITE_SIZE + MIN_NUMBER));
	if (floorUnder(board))
		board.digOnFloor(*this);
	moveSpritePosition(getDirection(direction == Direction::LEFT ? Direction::RIGHT : Direction::LEFT)
		* (STATIC_SPRITE_SIZE + (STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE)));
	moveSpritePosition(getDirection(Direction::UP) * (DYNAMIC_SPRITE_SIZE + MIN_NUMBER));
}
//-----------------------------------------------------------------------------
void Player::handleCollision(GameObjects& gameObject) 
{
	if (&gameObject == this) return;
	//double dispatch
	gameObject.handleCollision(*this);
}
//-----------------------------------------------------------------------------
void Player::handleCollision(Player& gameObject){}
//-----------------------------------------------------------------------------
void Player::handleCollision(Enemy& gameObjects) 
{
	Music::instance().startKilledSound();
	lessLives();
}
//-----------------------------------------------------------------------------
void Player::handleCollision(Wall& gameObjects) 
{
	alignWithWall(gameObjects);
}
//-----------------------------------------------------------------------------
void Player::handleCollision(Ladder& gameObject)
{
	if (aboveOrBelow())
		alignWithLadder(gameObject);
}
//-----------------------------------------------------------------------------
void Player::handleCollision(Rope& gameObject)
{
	alignWithRope(gameObject);
}
//-----------------------------------------------------------------------------
void Player::handleCollision(Vaccine& gameObjects)
{
	Music::instance().startCoinSound();
	m_points += 2 * m_level;
	m_texts[1].setString("Points:" + std::to_string(m_points));
}
//-----------------------------------------------------------------------------
void Player::handleCollision(SocialDistance& gameObjects)
{
	moreLives();
	m_texts[0].setString("Lives:" + std::to_string(m_lives));

}
//-----------------------------------------------------------------------------
void Player::handleCollision(Mutation& gameObject){}