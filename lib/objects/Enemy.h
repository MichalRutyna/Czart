#pragma once

#include "Entity.h"
#include "../functionality/Animated.h"
#include "../objects/Hero.h"

class Enemy : public Entity, public Animated
{
private:
	std::shared_ptr<Hero> mHero;
	std::shared_ptr<LTexture> texture_idle;
	std::shared_ptr<LTexture> texture_run;
	std::shared_ptr<LTexture> texture_attack;
	int state = 0;
	std::vector<std::shared_ptr<SDL_Rect>> attack_clips;
	int cooldown = 0;
public:
	Enemy(rendererType& r, textureType t_i, textureType t_r, textureType t_a, cameraType c);
    void render();
	void update(int dt);
	void setHero(std::shared_ptr<Hero> hero);
	void attack();

};
