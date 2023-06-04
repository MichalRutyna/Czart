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

void GameObjectHandler::subscribeInterface(drawablePointer object)
{
	interfaceLayer.push_back(object);
}

void GameObjectHandler::subscribeUpdatable(updatablePointer object)
{
	updatableObjects.push_back(object);
}

void GameObjectHandler::subscribeEvents(eventPointer object)
{
	eventObjects.push_back(object);
}

// ----------------------------------------------------------------------------------------------------------------------------
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

void GameObjectHandler::unsubscribeInterface(drawablePointer object)
{
	interfaceLayer.erase(std::remove(interfaceLayer.begin(), interfaceLayer.end(), object), interfaceLayer.end());
}

void GameObjectHandler::unsubscribeUpdatable(updatablePointer object)
{
	updatableObjects.erase(std::remove(updatableObjects.begin(), updatableObjects.end(), object), updatableObjects.end());
}

void GameObjectHandler::unsubscribeEvents(eventPointer object)
{
	eventObjects.erase(std::remove(eventObjects.begin(), eventObjects.end(), object), eventObjects.end());
}

// ----------------------------------------------------------------------------------------------------------------------------
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

std::vector<drawablePointer> GameObjectHandler::getInterfaceLayer()
{
	return interfaceLayer;
}

std::vector<updatablePointer> GameObjectHandler::getUpdatableObjects()
{
	return updatableObjects;
}

std::vector<eventPointer> GameObjectHandler::getEventObjects()
{
	return eventObjects;
}


void GameObjectHandler::markForRemoval(std::shared_ptr<_GameObject> object)
{
	objectsToRemove.push(object);
}

std::shared_ptr<_GameObject> GameObjectHandler::popRemoval()
{
	std::shared_ptr<_GameObject>& temp = objectsToRemove.front();
	objectsToRemove.pop();
	return temp;
}

void GameObjectHandler::markForAddition(std::shared_ptr<_GameObject> object)
{
	objectsToAdd.push(object);
}

std::shared_ptr<_GameObject> GameObjectHandler::popAddition()
{
	std::shared_ptr<_GameObject>& temp = objectsToAdd.front();
	objectsToAdd.pop();
	return temp;
}
