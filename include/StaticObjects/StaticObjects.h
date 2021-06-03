#pragma once
#include "GameObjects.h"

class StaticObjects : public GameObjects
{
public:
	StaticObjects(const sf::Texture& texture, Location location, float scale = RESIZE) : GameObjects(texture, location, scale){};
	virtual ~StaticObjects() = default;
	virtual void handleCollision(GameObjects& gameObject) override = 0;
	virtual void handleCollision(Player& gameObject) override = 0;
	virtual void handleCollision(Enemy& gameObject) override = 0;
	virtual void handleCollision(Wall& gameObject) override {};
	virtual void handleCollision(Ladder& gameObject) override {};
	virtual void handleCollision(Rope& gameObject) override {};
	virtual void handleCollision(Vaccine& gameObject) override {};
	virtual void handleCollision(SocialDistance& gameObject) override {};
	virtual void handleCollision(Mutation& gameObject) override {};
protected:
	
private:
};