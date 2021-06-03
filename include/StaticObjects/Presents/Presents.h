#pragma once
#include "StaticObjects\StaticObjects.h"
class Board;
class Presents : public StaticObjects
{
public:
	Presents(const sf::Texture& texture, Location location = Location()) : StaticObjects(texture, location), m_taken(false)
	{};

	bool isTaken()
	{
		return m_taken;
	};
	virtual void handleCollision(GameObjects& gameObject) override = 0;
	virtual void handleCollision(Player& gameObject) override = 0;
	virtual void handleCollision(Enemy& gameObject) override {};
protected:
	void set_taken()
	{
		m_taken = true;
	}
private:
	bool m_taken;

};