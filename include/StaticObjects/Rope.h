#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObjects.h"

class Rope : public StaticObjects
{
public:
	Rope(sf::Texture& texture, sf::Vector2f location) : StaticObjects(texture, location){};
protected:

private:

};