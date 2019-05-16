#include "DisplayNumbers.h"
#include "ObjectDisplay.h"



DisplayNumbers::DisplayNumbers()
{
	number0 = ObjectDisplay::texture("Numbers/zero.png");
	number1 = ObjectDisplay::texture("Numbers/one.png");
	number2 = ObjectDisplay::texture("Numbers/two.png");
	number3 = ObjectDisplay::texture("Numbers/three.png");
	number4 = ObjectDisplay::texture("Numbers/four.png");

	numberParameters.w = numberParameters.h = 32;
}


DisplayNumbers::~DisplayNumbers()
{
}

void DisplayNumbers::FindAndDisplayRightNumber(int chosenNumber, int rectX, int rectY)
{
	numberParameters.x = rectX;
	numberParameters.y = rectY;

	switch (chosenNumber)
	{
	case 0:
		ObjectDisplay::ImageDisplay(number0, numberParameters);
		break;
	case 1:
		ObjectDisplay::ImageDisplay(number1, numberParameters);
		break;
	case 2:
		ObjectDisplay::ImageDisplay(number2, numberParameters);
		break;
	case 3:
		ObjectDisplay::ImageDisplay(number3, numberParameters);
		break;
	case 4:
		ObjectDisplay::ImageDisplay(number4, numberParameters);
		break;
	default:
		break;
	}
}
