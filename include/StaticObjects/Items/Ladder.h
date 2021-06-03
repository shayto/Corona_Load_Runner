#pragma once
#include "StaticObjects\StaticObjects.h"

class Ladder : public StaticObjects
{
public:
	Ladder(const sf::Texture& texture, Location location) : StaticObjects(texture, location) {};
   virtual void handleCollision(GameObjects& gameObject) override
    {
        if (&gameObject == this) return;
        // double dispatch
        gameObject.handleCollision(*this);
    }
   virtual void handleCollision(Player& gameObject) override
   {
       gameObject.handleCollision(*this);
   };
   virtual void handleCollision(Enemy& gameObject) override
   {
       gameObject.handleCollision(*this);
   };
protected:

private:

};