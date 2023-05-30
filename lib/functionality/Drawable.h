#pragma once
class Drawable
{
public:
	Drawable() {};
	virtual ~Drawable() {};

	virtual void render() = 0;
};

