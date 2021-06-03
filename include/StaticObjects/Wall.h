#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObjects.h"

class Wall : public StaticObjects
{
public:
	Wall(sf::Texture texture, sf::Vector2f location) : StaticObjects(texture, location) {};

protected:

private:

};