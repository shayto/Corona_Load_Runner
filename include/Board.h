#pragma once
#include "GameObjects.hpp"
#include "Textures.h"
#include <algorithm>
#include <typeinfo>
#include <vector>
#include <fstream>
#include <cmath>
#include <optional>

typedef std::vector < std::vector<std::unique_ptr<GameObjects>>> objectsArr;

class Board
{
public:
	Board();
	~Board();
	float getBoardHeight() const;
	float getBoardWidth() const;
	void draw_objects(sf::RenderWindow& window);
	void moveObject(objectsType type, sf::Time DeltaTime, const std::optional<sf::Keyboard::Key>& key = std::nullopt);
	bool isObject(const MovingObjects& object, objectsType type) const;
	bool isInBoundries(const MovingObjects& object) const;
	Location getPlayerLocation() const;
	void digOnFloor(const MovingObjects& object);
	bool gameOver() const;
protected:

private:
	const static auto OBJECTS = 5;
	const static auto FLOORTIME = 5;
	const static auto DIGGEDNUMBER = 2;
	objectsArr m_objects;
	std::vector<std::unique_ptr<GameObjects>> m_diggedWalls;
	std::vector<sf::Time> m_diggedTimers;
	sf::Time m_levelTime;
	sf::Text m_showTime;
	sf::Font m_font;
	int m_vaccines;
	bool m_integratedTime;
	bool m_gameOver;
	void initializeLevel();
	bool LevelUp()const;
	void returnDiggedFloor(int index);
	std::streamoff m_beginLine, m_upToLine;//start of board and end of board
	std::unique_ptr<GameObjects> createObject(objectsType type, Location location);
	std::unique_ptr<GameObjects> createObject(Location location, int lives, int points, int level);
	std::unique_ptr<GameObjects> createObject(enemiesType type, Location location);
	std::unique_ptr<GameObjects> createObject(presentsType type, Location location);
	std::unique_ptr<GameObjects> createRandomObjects(objectsType type, int objectsNumbers, Location location);
	int objectIndex(objectsType type) const;
	int textureIndex(objectsType type) const;
	int textureIndex(enemiesType type) const;
	int textureIndex(presentsType type) const;
	void handleCollisions(GameObjects& gameObject);
	sf::Texture const& getTexture(int index) const;
	bool isPlayerDead() const;
	void clearUsedPresents();
	void openUsedPresents(const GameObjects& object);
	void setLockDown();
	void enterMutation();
	void SetTimeString();
	bool timesUp();
};