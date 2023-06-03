#include "../../lib/functionality/GameObjectHandler.h"

#include <algorithm>

GameObjectHandler::GameObjectHandler()
{
}

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
	backgroundLayer.erase(std::remove(backgroundLayer.begin(), backgroundLayer.end(), object), backgroundLayer.end());
}

void GameObjectHandler::unsubscribePlayerLayer(drawablePointer object)
{
	playerLayer.erase(std::remove(playerLayer.begin(), playerLayer.end(), object), playerLayer.end());
}

void GameObjectHandler::unsubscribeForeground(drawablePointer object)
{
	foregroundLayer.erase(std::remove(foregroundLayer.begin(), foregroundLayer.end(), object), foregroundLayer.end());
}

void GameObjectHandler::unsubscribeMoving(movingPointer object)
{
	movingObjects.erase(std::remove(movingObjects.begin(), movingObjects.end(), object), movingObjects.end());
}

void GameObjectHandler::unsubscribeUpdatable(updatablePointer object)
{
	updatableObjects.erase(std::remove(updatableObjects.begin(), updatableObjects.end(), object), updatableObjects.end());
}

std::vector<drawablePointer> GameObjectHandler::getBackgroundLayer()
{
	return backgroundLayer;
}

std::vector<drawablePointer> GameObjectHandler::getPlayerLayer()
{
	return playerLayer;
}

std::vector<drawablePointer> GameObjectHandler::getForegroundLayer()
{
	return foregroundLayer;
}

std::vector<movingPointer> GameObjectHandler::getMovingObjects()
{
	return movingObjects;
}

std::vector<updatablePointer> GameObjectHandler::getUpdatableObjects()
{
	return updatableObjects;
}
