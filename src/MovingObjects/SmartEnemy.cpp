#include "MovingObjects/Enemy/SmartEnemy.h"
#include "MovingObjects/MovingObjects.h"
#include "Board.h"
//-----------------------------------------------------------------------------
SmartEnemy::SmartEnemy(const sf::Texture& texture, Location location) : Enemy(texture, location) {};
//-----------------------------------------------------------------------------
void SmartEnemy::move(sf::Time DeltaTime, Board& board, const sf::Keyboard::Key& key)
{
	updatePrevPosition();
	auto playerLocation = board.getPlayerLocation();
	if (playerLocation.x != -1)
		if (playerLocation.y - MIN_NUMBER < getSpriteLocation().y && checkIfObject(board, objectsType::ladder))
			moveSpritePosition(getDirection(Direction::UP) * DeltaTime.asSeconds() * SPEED_PER_SECONDS/ (float)slowSpeed);
		else if (playerLocation.x + 10.f > getSpriteLocation().x)
			moveSpritePosition(getDirection(Direction::RIGHT) * DeltaTime.asSeconds() * SPEED_PER_SECONDS/ (float)slowSpeed);
		else if(playerLocation.x - 10.f < getSpriteLocation().x)
			moveSpritePosition(getDirection(Direction::LEFT) * DeltaTime.asSeconds() * SPEED_PER_SECONDS / (float)slowSpeed);
		else if (playerLocation.y > getSpriteLocation().y && LadderOrRope(board))
		moveSpritePosition(getDirection(Direction::DOWN) * DeltaTime.asSeconds() * SPEED_PER_SECONDS / (float)slowSpeed);
	else
		moveSpritePosition(getDirection(Direction::LEFT) * DeltaTime.asSeconds() * SPEED_PER_SECONDS / (float)slowSpeed);
	validMove(board);
}