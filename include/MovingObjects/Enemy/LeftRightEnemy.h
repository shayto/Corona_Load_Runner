#pragma once
#include "Enemy.h"

class LeftRightEnemy : public Enemy
{
public:
	LeftRightEnemy(const sf::Texture& texture, Location location) : Enemy(texture, location), 
		m_direction((Direction)(rand() % 2)){};
	void draw() {};
	virtual void move(sf::Time DeltaTime, Board& board, const sf::Keyboard::Key& key) override
	{
		updatePrevPosition();
		moveSpritePosition(getDirection(m_direction) * SPEED_PER_SECONDS / (float)slowSpeed * DeltaTime.asSeconds());
		if (!inBounderies(board))
		{
			changeDirection();
			alignWithBoard(board);
		}
		validMove(board);
	}
	
	virtual void handleCollision(Wall& gameObjects) override
	{
		changeDirection();
		alignWithWall(gameObjects);
	}
	virtual void handleCollision(Vaccine& gameObjects) override {};
protected:


private:
	const static auto slowSpeed = 5;
	Direction m_direction;
	void changeDirection() { m_direction = (m_direction == Direction::RIGHT) ? Direction::LEFT : Direction::RIGHT; };
};