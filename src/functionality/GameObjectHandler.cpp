#include "../../lib/functionality/GameObjectHandler.h"

#include <algorithm>

void GameObjectHandler::subscribeBackground(drawablePointer object)
{
	backgroundLayer.push_back(object);
}

void GameObjectHandler::subscribePlayerLayer(drawablePointer object)
{
	playerLayer.push_back(object);
}

void GameObjectHandler::subscribeForeground(drawablePointer object)
{
	foregroundLayer.push_back(object);
}

void GameObjectHandler::subscribeMoving(movingPointer object)
{
	movingObjects.push_back(object);
}

void GameObjectHandler::subscribeUpdatable(updatablePointer object)
{
	updatableObjects.push_back(object);
}

void GameObjectHandler::unsubscribeBackground(drawablePointer object)
{
	backgroundLayer.
}

void GameObjectHandler::unsubscribePlayerLayer(drawablePointer object)
{
}

void GameObjectHandler::unsubscribeForeground(drawablePointer object)
{
}

void GameObjectHandler::unsubscribeMoving(movingPointer object)
{
}

void GameObjectHandler::unsubscribeUpdatable(updatablePointer object)
{
}

std::vector<drawablePointer> GameObjectHandler::getBackgroundLayer()
{
	return std::vector<drawablePointer>();
}

std::vector<drawablePointer> GameObjectHandler::getPlayerLayer()
{
	return std::vector<drawablePointer>();
}

std::vector<drawablePointer> GameObjectHandler::getForegroundLayer()
{
	return std::vector<drawablePointer>();
}

std::vector<movingPointer> GameObjectHandler::getMovingObjects()
{
	return std::vector<movingPointer>();
}

std::vector<updatablePointer> GameObjectHandler::getUpdatableObjects()
{
	return std::vector<updatablePointer>();
}
