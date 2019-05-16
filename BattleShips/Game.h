#pragma once
#include "SDL.h"
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


class Game {
public:
	void CreateWindow();
	void Update();
	void Draw();
	void Destroy();

	static SDL_Renderer *renderer;

	bool GetisRunning();
private:
	bool isRunning = true, isPlayerTurn = true;
	SDL_Window *window;
};

