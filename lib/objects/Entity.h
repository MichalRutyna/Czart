#pragma once
class Entity : public DMovable
{
protected:
	int MAX_HP;
	int MAX_MANA;

	int mHp, mMana;

public:

	int getHp();
	int getMana();

	Entity(rendererType& renderer, textureType tekstura, cameraType kamera) : DMovable(renderer, tekstura, kamera) {}
};

