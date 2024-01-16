#pragma once

class GameObj
{
protected:
	virtual void draw() = 0;
	virtual void update() = 0;
};