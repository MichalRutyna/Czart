#pragma once

#include <memory>
#include <vector>
#include "Drawable.h"
#include "Updatable.h"
#include "../rendering/Moving.h"

typedef std::shared_ptr<Drawable> drawablePointer;
typedef std::shared_ptr<Moving> movingPointer;
typedef std::shared_ptr<Updatable> updatablePointer;


class GameObjectHandler
{
private:
    std::vector<drawablePointer> backgroundLayer;   // background only
    std::vector<drawablePointer> playerLayer;       // player, monsters, walls
    std::vector<drawablePointer> foregroundLayer;   // things which should obstruct view

    std::vector<movingPointer> movingObjects;
    std::vector<updatablePointer> updatableObjects;

public:
    void subscribeBackground(drawablePointer);
    void subscribePlayerLayer(drawablePointer);
    void subscribeForeground(drawablePointer);

    void subscribeMoving(movingPointer);
    void subscribeUpdatable(updatablePointer);

    void unsubscribeBackground(drawablePointer);
    void unsubscribePlayerLayer(drawablePointer);
    void unsubscribeForeground(drawablePointer);

    void unsubscribeMoving(movingPointer);
    void unsubscribeUpdatable(updatablePointer);

    std::vector<drawablePointer> getBackgroundLayer();
    std::vector<drawablePointer> getPlayerLayer();
    std::vector<drawablePointer> getForegroundLayer();

    std::vector<movingPointer> getMovingObjects();
    std::vector<updatablePointer> getUpdatableObjects();


};

