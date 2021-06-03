#pragma once
#include "GameObjects.h"

class Board;
const static float SPEED_PER_SECONDS = DYNAMIC_SPRITE_SIZE * 10.f;
class MovingObjects : public GameObjects
{
public:
	MovingObjects(const sf::Texture& texture, Location location);
	virtual ~MovingObjects() = default;
	virtual void move(sf::Time DeltaTime, Board& board, const sf::Keyboard::Key& key) = 0;
	virtual void handleCollision(GameObjects& gameObject) override = 0;
	virtual void handleCollision(Player& gameObject) override = 0;
	virtual void handleCollision(Enemy& gameObject) override = 0;
	virtual void handleCollision(Wall& gameObjects) override = 0;
	virtual void handleCollision(Ladder& gameObject) override = 0;
	virtual void handleCollision(Rope& gameObject) override = 0;
	virtual void handleCollision(Vaccine& gameObject) override = 0;
	virtual void handleCollision(SocialDistance& gameObjects) override = 0;
	virtual void handleCollision(Mutation& gameObject) override = 0;
	void MoveAboveWall();
protected:
	void updatePrevPosition();
	void restorePosition();
	void validMove(const Board& board);
	void alignWithWall(const Wall& gameObjects);
	void alignWithBoard(const Board& board);
	void alignWithLadder(const Ladder& object);
	void alignWithRope(const Rope& object);
	bool checkIfObject(const Board& board, objectsType type) const;
	bool inBounderies(const Board& board);
	bool aboveOrBelow() const;
	bool below() const;
	bool above() const;
	bool checkIfUpDown(const Board& board);
	bool floorUnder(const Board& board);
	bool LadderOrRope(const Board& board);
	enum class Direction : int
	{
		LEFT, RIGHT, UP, DOWN, DEFAULT
	};
	Location getDirection(MovingObjects::Direction direction) const;
private:
	const static auto slowSpeed = 15;
	Location m_previousLocation;
};