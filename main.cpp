#include "sgg\graphics.h"
#include  "define.h"
#include "Game.h"
#include <string>
#include<stdio.h>
#include<time.h>

void draw()
{
	Game* mygame = Game::getInstance();
	mygame->draw();
}
void update(float ms)
{
	Game* myGame = Game::getInstance();

	myGame->update();
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	graphics::createWindow(640, 560, "BJ v0.1");
	Game* game = Game::getInstance();

	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::setDrawFunction(draw);

	graphics::setUpdateFunction(update);

	graphics::startMessageLoop();

	Game::releaseInstance();
	return 0;
}