#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObjects.h"

class Ladder : public StaticObjects
{
public:
	Ladder(sf::Texture& texture, sf::Vector2f location) : StaticObjects(texture, location) {};
	void draw() {};

protected:

private:

};