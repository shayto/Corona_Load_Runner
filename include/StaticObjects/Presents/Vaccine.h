#pragma once
#include "StaticObjects\Presents\Presents.h"
class Vaccine : public Presents
{
public:
	Vaccine(const sf::Texture& texture, Location location) : Presents(texture, location)
    {};

    virtual void handleCollision(GameObjects& gameObject) override
    {
        if (&gameObject == this) return;
        //double dispatch
        gameObject.handleCollision(*this);
    }
    virtual void handleCollision(Player& gameObject) override
    {
        set_taken();
        gameObject.handleCollision(*this);
    };
protected:
private:
    
};

