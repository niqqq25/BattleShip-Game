#include "Buttons.h"
#include "ObjectDisplay.h"
#include "HendleEvents.h"

Buttons::Buttons(){}

Buttons::Buttons(const char * buttonname, int button_x, int button_y, int button_w, int button_h)
{
	button = ObjectDisplay::texture(buttonname);

	DestR.x = button_x;
	DestR.y = button_y;
	DestR.w = button_w;
	DestR.h = button_h;
}


bool Buttons::ButtonCheck()
{
	correctpress = false;
	if (DestR.x <= HendleEvents::mouseXCoord && DestR.x + DestR.w >= HendleEvents::mouseXCoord && DestR.y <= HendleEvents::mouseYCoord && DestR.y + DestR.h >= HendleEvents::mouseYCoord) {
		correctpress = true;
	}
	return correctpress;
}

void Buttons::DisplayButton()
{
	ObjectDisplay::ImageDisplay(button, DestR);
}

void Buttons::setisButtonPressedCorrect(bool setValue)
{
	isButtonPressedCorrect = setValue;
}

bool Buttons::getisButtonPressedCorrect()
{
	return isButtonPressedCorrect;
}
