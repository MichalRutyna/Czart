#pragma once
class Entity
{
protected:
	int MAX_HP;
	int MAX_MANA;

	int mHp, mMana;

public:
	int getHp();
	int getMana();
};

