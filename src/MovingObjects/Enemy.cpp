#pragma once
#include "MovingObjects/Enemy/Enemy.h"
#include "MovingObjects/Player/Player.h"
#include "StaticObjects/Items/Ladder.h"
//-----------------------------------------------------------------------------
	Enemy::Enemy(const sf::Texture& texture, Location location) : MovingObjects(texture, location) 
	{};
	void Enemy::handleCollision(GameObjects& gameObject) 
	{
		if (&gameObject == this) return;
		gameObject.handleCollision(*this);
	}
//-----------------------------------------------------------------------------
	void Enemy::handleCollision(Player& gameObject)
	{
		// call the player so it can decrease its own live count
		gameObject.handleCollision(*this);
	}
//-----------------------------------------------------------------------------
	void Enemy::handleCollision(Enemy& gameObject) 
	{
		// ignore
	}
//-----------------------------------------------------------------------------
	void Enemy::handleCollision(Wall& gameObjects) 
	{
		alignWithWall(gameObjects);
	}
//-----------------------------------------------------------------------------
	void Enemy::handleCollision(Ladder& gameObject)
	{
		if (aboveOrBelow())
			alignWithLadder(gameObject);
	}
//-----------------------------------------------------------------------------
	void Enemy::handleCollision(Rope& gameObject)
	{
		alignWithRope(gameObject);
	}
//-----------------------------------------------------------------------------
	void Enemy::handleCollision(Vaccine& gameObjects){}
//-----------------------------------------------------------------------------
	void Enemy::handleCollision(SocialDistance& gameObjects){}
//-----------------------------------------------------------------------------
	void Enemy::handleCollision(Mutation& gameObjects){}