#pragma once
#include "MovingObjects/MovingObjects.h"
#include "Music.h"
class Player : public MovingObjects
{
public:
	Player(const sf::Texture& texture, Location location = Location(), int lives = 3, int points = 0, int level = 1);
	virtual void draw(sf::RenderWindow& window) override;
	virtual void move(sf::Time DeltaTime, Board& board, const sf::Keyboard::Key& key) override;
	bool isDead() const;
	void reborn();
	void lessLives();
	int getPoints()const;
	int getLives()const;
	int getLevel()const;
	virtual void handleCollision(GameObjects& gameObject) override;
	virtual void handleCollision(Player& gameObject) override;
	virtual void handleCollision(Enemy& gameObjects) override;
	virtual void handleCollision(Wall& gameObjects) override;
	virtual void handleCollision(Ladder& gameObject) override;
	virtual void handleCollision(Rope& gameObject) override;
	virtual void handleCollision(Vaccine& gameObjects) override;
	virtual void handleCollision(SocialDistance& gameObjects) override;
	virtual void handleCollision(Mutation& gameObject) override;
protected:

private:
	const static int TEXTS = 3;
	Location m_initialLocation;
	std::array <sf::Text, TEXTS> m_texts;
	sf::Font m_font;
	int m_level;
	int m_lives;
	int m_points;
	int m_initialPoints;
	bool m_killed;
	void initilizeFontText();
	void moreLives();
	void digWall(Board& board, MovingObjects::Direction direction);
};