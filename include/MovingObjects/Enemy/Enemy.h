#pragma once
#include "MovingObjects/MovingObjects.h"

class Enemy : public MovingObjects
{
public:
	Enemy(const sf::Texture& texture, Location location);
	virtual ~Enemy() = default;
	virtual void move(sf::Time DeltaTime, Board& board, const sf::Keyboard::Key& key) override = 0;
	virtual void handleCollision(GameObjects& gameObject) override;
	virtual void handleCollision(Player& gameObject) override;
	virtual void handleCollision(Enemy& gameObject) override;
	virtual void handleCollision(Wall& gameObjects) override;
	virtual void handleCollision(Ladder& gameObject) override;
	virtual void handleCollision(Rope& gameObject) override;
	virtual void handleCollision(Vaccine& gameObjects) override;
	virtual void handleCollision(SocialDistance& gameObjects) override;
	virtual void handleCollision(Mutation& gameObjects) override;

protected:
private:
};