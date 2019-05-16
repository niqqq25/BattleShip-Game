#pragma once
#include "Game.h"


class HendleEvents {
public:
	HendleEvents();
	~HendleEvents();
	void EventType();
	bool isClickedOnRihtField(SDL_Rect fieldParameters);
	void ConvertMousePosToBoardCoord(int &boardYCoord, int &boardXCord, SDL_Rect fieldParameters);

	static int EventCode, MouseEvent, mouseXCoord, mouseYCoord; 
	//EventCode 2 - buildingMode, EventCode 3 - shootingMode, EventCode 4 - player won, EventCode 5 - bot won
private:
	bool isButtonPressed = false;
	SDL_Event event;

};

