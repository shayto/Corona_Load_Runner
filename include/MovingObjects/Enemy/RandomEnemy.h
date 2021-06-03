#pragma once
#include "Enemy.h"
class RandomEnemy : public Enemy
{
public:
	RandomEnemy(const sf::Texture& texture, Location location) : Enemy(texture, location) {};
	virtual void move(sf::Time DeltaTime, Board& board, const sf::Keyboard::Key& key) override
	{
		updatePrevPosition();
		moveSpritePosition(getDirection((Direction)(rand() % 4)) * SPEED_PER_SECONDS/(float)slowSpeed * DeltaTime.asSeconds());
		validMove(board);
	}
protected:

private:
	const static auto slowSpeed = 2;
};