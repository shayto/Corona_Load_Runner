#pragma once
#include "Enemy.h"
class SmartEnemy : public Enemy
{
public:
	SmartEnemy(const sf::Texture& texture, Location location);
	virtual void move(sf::Time DeltaTime, Board& board, const sf::Keyboard::Key& key) override;
	
protected:

private:
	const static auto slowSpeed = 15;
};