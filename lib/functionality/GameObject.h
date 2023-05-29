#pragma once
class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};

	virtual void render() = 0;
};

