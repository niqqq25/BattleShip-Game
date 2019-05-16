#include "HendleEvents.h"
#include <iostream>

int HendleEvents::EventCode = NULL;
int HendleEvents::MouseEvent = NULL;
int HendleEvents::mouseXCoord = NULL;
int HendleEvents::mouseYCoord = NULL;

HendleEvents::HendleEvents()
{
	//<-- Where other windows are created
	EventCode = 1; //<- No mouse events happen
}

HendleEvents::~HendleEvents()
{
}

void HendleEvents::EventType()
{
	//EventCode = 1;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT) {
		EventCode = 0;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && isButtonPressed == false) {
		MouseEvent = 1; // <- New mouse left click down
		isButtonPressed = true;
		mouseXCoord = event.button.x;
		mouseYCoord = event.button.y;
	}
	else if (event.button.button = SDL_BUTTON_LEFT && isButtonPressed == true) {
		mouseXCoord = event.button.x;
		mouseYCoord = event.button.y;
		MouseEvent = 2; // <- Mouse left click down
	}
	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT && isButtonPressed == true) {
		mouseXCoord = event.button.x;
		mouseYCoord = event.button.y;
		MouseEvent = 3;// <- Mouse left click up
		isButtonPressed = false;
	}
}

bool HendleEvents::isClickedOnRihtField(SDL_Rect fieldParameters)
{
	if (event.button.x > fieldParameters.x && event.button.x < fieldParameters.w + fieldParameters.x) {
		if (event.button.y > fieldParameters.y && event.button.y < fieldParameters.h + fieldParameters.y) {
			return true;
		}
	}
	return false;
}

void HendleEvents::ConvertMousePosToBoardCoord(int & boardYCoord, int & boardXCoord, SDL_Rect fieldParameters)
{
	boardYCoord = (event.button.y - fieldParameters.y) / 32;
	boardXCoord = (event.button.x - fieldParameters.x) / 32;
}

