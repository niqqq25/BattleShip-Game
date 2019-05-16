#pragma once
#include "Game.h"


class DisplayNumbers
{
public:
	DisplayNumbers();
	~DisplayNumbers();
	void FindAndDisplayRightNumber(int chosenNumber, int rectX, int rectY);

private:
	SDL_Texture *number0, *number1, *number2, *number3, *number4;
	SDL_Rect numberParameters;
};

