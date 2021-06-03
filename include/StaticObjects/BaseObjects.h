#pragma once
#include "StaticObjects.h"
#include "MovingObjects/MovingObjects.h"

class BaseObjects : public StaticObjects
{
public:
    BaseObjects(const sf::Texture& texture, Location location = Location()) : StaticObjects(texture, Location(), (float)BACKGROUNDRE_RESIZE),
        m_gameBoarders(sf::RectangleShape(location * STATIC_SPRITE_SIZE))
    {
        setSpriteSize((int)m_gameBoarders.getSize().x, (int)m_gameBoarders.getSize().y);
        m_gameBoarders.setFillColor(sf::Color::Transparent);
    };
    virtual void handleCollision(GameObjects& gameObject) override {}
    virtual void handleCollision(Player& gameObject) override {};
    virtual void handleCollision(Enemy& gameObject) override {};
 
    virtual void draw(sf::RenderWindow& window)
    {
        window.draw(getSprite());
        window.draw(m_gameBoarders);
    }

    bool inBounderies(const MovingObjects& object) const
    {
        return m_gameBoarders.getGlobalBounds().contains(object.getSpriteLocation()) &&
            m_gameBoarders.getGlobalBounds().contains(object.getSpriteLocation().x + DYNAMIC_SPRITE_SIZE - 0.01f, object.getSpriteLocation().y + DYNAMIC_SPRITE_SIZE - MIN_NUMBER);
    }

    bool inBounderies(const Location& TopLeft, const Location& ButtomRight) const
    {
        return m_gameBoarders.getGlobalBounds().contains(TopLeft) &&
            m_gameBoarders.getGlobalBounds().contains(Location(ButtomRight.x + STATIC_SPRITE_SIZE - 0.01f, ButtomRight.y + STATIC_SPRITE_SIZE - MIN_NUMBER));
    }
    float getHeight() const
    {
        return m_gameBoarders.getGlobalBounds().height;
    }

    float getWidth() const
    {
        return m_gameBoarders.getGlobalBounds().width;
    }
private:
    sf::RectangleShape m_gameBoarders;
    const static auto BACKGROUNDRE_RESIZE = 1;
};