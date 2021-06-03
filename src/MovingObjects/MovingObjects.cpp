#pragma once
#include "MovingObjects/MovingObjects.h"
#include "Board.h"
//-----------------------------------------------------------------------------
MovingObjects::MovingObjects(const sf::Texture& texture, Location location) : 
			   GameObjects(texture, location, DYNAMIC_RESIZE) {};
//-----------------------------------------------------------------------------
void MovingObjects::updatePrevPosition()
{
	m_previousLocation = getSpriteLocation();
}
//-----------------------------------------------------------------------------
void MovingObjects::restorePosition()
{
	setSpritePosition(m_previousLocation);
}
//-----------------------------------------------------------------------------
bool MovingObjects::aboveOrBelow() const
{
	return getSpriteLocation().y != m_previousLocation.y;
}
//-----------------------------------------------------------------------------
bool MovingObjects::below() const
{
	return getSpriteLocation().y > m_previousLocation.y;
}
//-----------------------------------------------------------------------------
bool MovingObjects::above() const
{
	return getSpriteLocation().y < m_previousLocation.y;
}
//-----------------------------------------------------------------------------
void MovingObjects::alignWithWall(const Wall& gameObjects)
{
	if (getSpriteLocation().x > m_previousLocation.x)//tried to go right
		setSpritePosition(Location(gameObjects.getSpriteLocation().x - DYNAMIC_SPRITE_SIZE - MIN_NUMBER, m_previousLocation.y));
	else if (getSpriteLocation().x < m_previousLocation.x)//tried to go left
		setSpritePosition(Location(gameObjects.getSpriteLocation().x + STATIC_SPRITE_SIZE + MIN_NUMBER, m_previousLocation.y));
	else if (getSpriteLocation().y > m_previousLocation.y)//tried to down
		setSpritePosition(Location(m_previousLocation.x, gameObjects.getSpriteLocation().y - DYNAMIC_SPRITE_SIZE - MIN_NUMBER));
	else if (getSpriteLocation().y < m_previousLocation.y)//tried to go up
		setSpritePosition(Location(m_previousLocation.x, gameObjects.getSpriteLocation().y + DYNAMIC_SPRITE_SIZE + MIN_NUMBER));
}
//-----------------------------------------------------------------------------
void MovingObjects::alignWithLadder(const Ladder& object)
{
	if (getSpriteLocation().x + (STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE) / 2 != object.getSpriteLocation().x)
		setSpritePosition(Location(object.getSpriteLocation().x + (STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE) / 2, getSpriteLocation().y));
}
//-----------------------------------------------------------------------------
void MovingObjects::alignWithRope(const Rope& object)
{
	if (getSpriteLocation().y - STATIC_SPRITE_SIZE - (STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE) != object.getSpriteLocation().y)
		setSpritePosition(Location(getSpriteLocation().x, object.getSpriteLocation().y +
			STATIC_SPRITE_SIZE - DYNAMIC_SPRITE_SIZE));
}
//-----------------------------------------------------------------------------
Location MovingObjects::getDirection(MovingObjects::Direction direction) const
{
	switch (direction)
	{
	case Direction::RIGHT:
		return Location(1, 0);
	case Direction::LEFT:
		return Location(-1, 0);
	case Direction::UP:
		return Location(0, -1);
	case Direction::DOWN:
		return Location(0, 1);
	default:
		return Location();
	}
}
//-----------------------------------------------------------------------------
void MovingObjects::validMove(const Board& board)
{
	while (!floorUnder(board))
	{
		if (!inBounderies(board) || LadderOrRope(board))
		{
			alignWithBoard(board);
			break;
		}
		updatePrevPosition();
		moveSpritePosition(getDirection(Direction::DOWN) * DYNAMIC_SPRITE_SIZE);
	}
}
//-----------------------------------------------------------------------------
bool MovingObjects::inBounderies(const Board& board)
{
	return board.isInBoundries(*this);
}
//-----------------------------------------------------------------------------
bool MovingObjects::checkIfObject(const Board& board, objectsType type) const
{
	return board.isObject(*this, type);
}
//-----------------------------------------------------------------------------
bool MovingObjects::checkIfUpDown(const Board& board)
{
	return aboveOrBelow();
}
//-----------------------------------------------------------------------------
void MovingObjects::alignWithBoard(const Board& board)
{
	if (getSpriteLocation().x + DYNAMIC_SPRITE_SIZE > board.getBoardWidth())
		setSpritePosition(Location(board.getBoardWidth() - DYNAMIC_SPRITE_SIZE, getSpriteLocation().y));
	else if (getSpriteLocation().x < 0.f)
		setSpritePosition(Location(0.f, getSpriteLocation().y));
	else if (getSpriteLocation().y + DYNAMIC_SPRITE_SIZE > board.getBoardHeight())
		setSpritePosition(Location(getSpriteLocation().x, board.getBoardHeight() - DYNAMIC_SPRITE_SIZE));
	else if (getSpriteLocation().y < 0.f)
		setSpritePosition(Location(getSpriteLocation().x, 0.f));
}
//-----------------------------------------------------------------------------
bool MovingObjects::floorUnder(const Board& board)
{
	moveSpritePosition(getDirection(Direction::DOWN) * MIN_NUMBER);
	auto result = checkIfObject(board, objectsType::wall);
	moveSpritePosition(getDirection(Direction::UP) * MIN_NUMBER);
	return result;
}
//-----------------------------------------------------------------------------
bool MovingObjects::LadderOrRope(const Board& board)
{
	moveSpritePosition(getDirection(Direction::DOWN) * MIN_NUMBER);
	auto result = checkIfObject(board, objectsType::ladder);
	moveSpritePosition(getDirection(Direction::UP) * MIN_NUMBER);
	return (result || (!below() && checkIfObject(board, objectsType::rope)));
}
//-----------------------------------------------------------------------------
void MovingObjects::MoveAboveWall()
{
	moveSpritePosition(getDirection(Direction::UP) * (STATIC_SPRITE_SIZE + MIN_NUMBER));
}