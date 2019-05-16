#pragma once
#include "Game.h"

class Buttons {
public:
	Buttons();
	Buttons(const char *buttonname, int button_x, int button_y, int button_w, int button_h);
	~Buttons();

	bool ButtonCheck();
	void DisplayButton();

	void setisButtonPressedCorrect(bool setValue);
	bool getisButtonPressedCorrect();

private:
	bool correctpress;
	bool isButtonPressedCorrect = false;
	SDL_Texture *button;
	SDL_Rect DestR;
};

