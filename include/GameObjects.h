#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
typedef sf::Vector2f Location;
class Window;
class Enemy;
class Player;
class Wall;
class Ladder;
class Rope;
class Vaccine;
class SocialDistance;
class Mutation;

static const auto RESIZE = 0.12f;
static const auto TEXTURESIZE = 512.f;
static const auto STATIC_SPRITE_SIZE = RESIZE * TEXTURESIZE;
static const auto MIN_NUMBER = 0.01f;
static const auto ENEMIES_TYPE = 3;
static const auto PRESENTS_TYPE = 3;
const static auto DYNAMIC_RESIZE = 0.75f * RESIZE;
const static auto DYNAMIC_SPRITE_SIZE = DYNAMIC_RESIZE * TEXTURESIZE;


enum class objectsType : char
{
	baseObjects, player = '@', ladder = 'H', wall = '#', rope = '-', 
	vaccine = '*', enemy = '%', presents = '+'
};

enum class enemiesType : int
{
	randomEnemy, leftrightEnemy, smartEnemy
};

enum class presentsType : int
{
	socialDistance, mutation, lockdown
};

class GameObjects
{
public:
	GameObjects(const sf::Texture& texture, Location location, float scale = RESIZE) : m_sprite(texture)
	{
		m_sprite.setScale(scale, scale);
		setSpritePosition(location);
	};
	virtual ~GameObjects() = default;
	Location const& getSpriteLocation() const
	{
		return getSprite().getPosition();
	};
	bool collides(const GameObjects& object) const
	{
		return getSprite().getGlobalBounds().intersects(object.getSprite().getGlobalBounds());
	}

	virtual void draw(sf::RenderWindow& window)
	{
		window.draw(getSprite());
	}

	void setSpriteSize(int width, int height)
	{
		m_sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	}

	virtual void handleCollision(GameObjects& gameObject) = 0;
	virtual void handleCollision(Player& gameObject) = 0;
	virtual void handleCollision(Enemy& gameObject) = 0;
	virtual void handleCollision(Wall& gameObject) = 0;
	virtual void handleCollision(Ladder& gameObject) = 0;
	virtual void handleCollision(Rope& gameObject) = 0;
	virtual void handleCollision(Vaccine& gameObjects) = 0;
	virtual void handleCollision(SocialDistance& gameObjects) = 0;
	virtual void handleCollision(Mutation& gameObject) = 0;
protected:
	sf::Sprite const& getSprite() const
	{
		return m_sprite;
	}

	void setSpritePosition(Location location)
	{
		m_sprite.setPosition(location);
	}

	void moveSpritePosition(Location location)
	{
		m_sprite.move(location);
	}

private:
	sf::Sprite m_sprite;
};

inline bool operator==(const GameObjects& lhs, const GameObjects& rhs)
{
	return lhs.collides(rhs);
}
