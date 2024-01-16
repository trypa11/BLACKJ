#pragma once
#include <random>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include<stdio.h>
#include<time.h>

inline void sleep(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#define CANVAS_WIDTH 16.0f                                     
#define CANVAS_HEIGHT 10.0f

#define ASSET_PATH ".\\assets\\"

#define BUTTON_WIDTH 2.0f
#define BUTTON_HEIGHT 1.0f

#define PLAYER_SIZE 1.0f

#define BACK_CARD_SIZE 0.5f;

#define CARD_SIZE 0.8f


#define SETCOLOR(c, r, g, b) { c[0] = r; c[1] = g; c[2] = b; }
#define RAND0TO1() (rand() / (float)RAND_MAX)

