#pragma once

#include <memory>
#include <vector>
#include "GameObjects.h"

typedef std::shared_ptr<_Drawable> drawablePointer;
typedef std::shared_ptr<_Movable> movingPointer;
typedef std::shared_ptr<_Updatable> updatablePointer;


class GameObjectHandler
{
private:
    std::vector<drawablePointer> backgroundLayer;   // background only
    std::vector<drawablePointer> playerLayer;       // player, monsters, walls
    std::vector<drawablePointer> foregroundLayer;   // things which should obstruct view

    std::vector<movingPointer> movingObjects;
    std::vector<updatablePointer> updatableObjects;

public:
    /*
    3 typy obiektów: _Drawable, _Updatable i specjalny _Movable (ró¿ni siê od updatable tym, ¿e ma dodatkowy krok przy obliczaniu ruchu)
    */
    GameObjectHandler();

    void subscribeBackground(drawablePointer object);
    void subscribePlayerLayer(drawablePointer object);
    void subscribeForeground(drawablePointer object);

    void subscribeMoving(movingPointer object);
    void subscribeUpdatable(updatablePointer object);

    void unsubscribeBackground(drawablePointer object);
    void unsubscribePlayerLayer(drawablePointer object);
    void unsubscribeForeground(drawablePointer object);

    void unsubscribeMoving(movingPointer object);
    void unsubscribeUpdatable(updatablePointer object);

    std::vector<drawablePointer> getBackgroundLayer();
    std::vector<drawablePointer> getPlayerLayer();
    std::vector<drawablePointer> getForegroundLayer();

    std::vector<movingPointer> getMovingObjects();
    std::vector<updatablePointer> getUpdatableObjects();


};

