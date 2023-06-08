#pragma once

#include <memory>
#include <vector>
#include <queue>
#include <list>
#include "GameObjects.h"

typedef std::shared_ptr<_Drawable> drawablePointer;
typedef std::shared_ptr<_Updatable> updatablePointer;
typedef std::shared_ptr<_HandlingEvents> eventPointer;



class GameObjectHandler
{
private:
    std::vector<drawablePointer> backgroundLayer;   // background only
    std::vector<drawablePointer> playerLayer;       // player, monsters, walls
    std::vector<drawablePointer> foregroundLayer;   // things which should obstruct view
    std::vector<drawablePointer> interfaceLayer;   // interface

    std::vector<updatablePointer> updatableObjects;
    std::vector<eventPointer> eventObjects;
    
    std::queue<std::shared_ptr<_GameObject>, std::list<std::shared_ptr<_GameObject>>> objectsToRemove;
    std::queue<std::shared_ptr<_GameObject>, std::list<std::shared_ptr<_GameObject>>> objectsToAdd;

public:
    /*
    3 typy obiektów: _Drawable, _Updatable i specjalny Movable (ró¿ni siê od updatable tym, ¿e ma dodatkowy krok przy obliczaniu ruchu)
    */
    GameObjectHandler();

    void subscribeBackground(drawablePointer object);
    void subscribePlayerLayer(drawablePointer object);
    void subscribeForeground(drawablePointer object);
    void subscribeInterface(drawablePointer object);

    void subscribeUpdatable(updatablePointer object);
    void subscribeEvents(eventPointer object);

    void unsubscribeBackground(drawablePointer object);
    void unsubscribePlayerLayer(drawablePointer object);
    void unsubscribeForeground(drawablePointer object);
    void unsubscribeInterface(drawablePointer object);

    void unsubscribeUpdatable(updatablePointer object);
    void unsubscribeEvents(eventPointer object);

    std::vector<drawablePointer> getBackgroundLayer();
    std::vector<drawablePointer> getPlayerLayer();
    std::vector<drawablePointer> getForegroundLayer();
    std::vector<drawablePointer> getInterfaceLayer();

    std::vector<updatablePointer> getUpdatableObjects();
    std::vector<eventPointer> getEventObjects();

    void markForRemoval(std::shared_ptr<_GameObject> object);
    std::shared_ptr<_GameObject> popRemoval();

    void markForAddition(std::shared_ptr<_GameObject> object);
    std::shared_ptr<_GameObject> popAddition();
};

