#include "Windows.h"
#include "HendleEvents.h"
#include "ObjectDisplay.h"
#include "Buttons.h"
#include "FunctionsWithArrays.h"
#include "DisplayNumbers.h"

Buttons *button, *button_pressed, *exitButton, *exitButton_pressed, *startButton, *startButton_pressed,
*playagainButton, *playagainButton_pressed, *continueButton, *continueButton_pressed;

DisplayNumbers * displaynumbers;


Windows::Windows()
{
	startGameWindow = ObjectDisplay::texture("Pictures/StartWindow.png");
	tryAgainWindow = ObjectDisplay::texture("Pictures/tryAgainWindow.png");
	playAgainWindow = ObjectDisplay::texture("Pictures/playAgainWindow.png");
	playerBuildingModeWindow = ObjectDisplay::texture("Pictures/BackgroundWithShipCount.png");
	shootingModeWindow = ObjectDisplay::texture("Pictures/ShootingShipsBackground.png");

	dstrect.x = 180;
	dstrect.y = 20;
	dstrect.w = 480;
	dstrect.h = 600;

	dstrect1.x = 0;
	dstrect1.y = 340;
	dstrect1.h = 300;
	dstrect1.w = 840;

	forBackgrounds.x = forBackgrounds.y = 0;
	forBackgrounds.h = 640;
	forBackgrounds.w = 840;

	button = new Buttons();
	button_pressed = new Buttons();

	startButton = new  Buttons("Buttons/startbutton.png", 324, 200, 192, 96);
	startButton_pressed = new Buttons("Buttons/startbutton_pressed.png", 324, 200, 192, 96);
	
	exitButton = new Buttons("Buttons/exitbutton.png", 324, 470, 192, 96);
	exitButton_pressed = new Buttons("Buttons/exitbutton_pressed.png", 324, 470, 192, 96);

	playagainButton = new  Buttons("Buttons/playagainbutton.png", 324, 250, 192, 96);
	playagainButton_pressed = new  Buttons("Buttons/playagainbutton_pressed.png", 324, 250, 192, 96);

	continueButton = new Buttons("Buttons/continuebutton.png", 545, 450, 192, 96);
	continueButton_pressed = new Buttons("Buttons/continuebutton_pressed.png", 545, 450, 192, 96);

	displaynumbers = new DisplayNumbers();
}


Windows::~Windows(){}

void Windows::StartGameWindow()
{
	ObjectDisplay::ImageDisplay(startGameWindow, forBackgrounds);
	button = startButton;
	button_pressed = startButton_pressed;
	ButtonAction(2);
	button = exitButton;
	button_pressed = exitButton_pressed;
	ButtonAction(0);
}

void Windows::TryAgainWindow()
{
	ObjectDisplay::ImageDisplay(tryAgainWindow, dstrect);
	button = playagainButton;
	button_pressed = playagainButton_pressed;
	ButtonAction(-1);// <--Restart
	button = exitButton;
	button_pressed = exitButton_pressed;
	ButtonAction(0);
}

void Windows::PlayAgainWindow()
{
	ObjectDisplay::ImageDisplay(playAgainWindow, dstrect);
	button = playagainButton;
	button_pressed = playagainButton_pressed;
	ButtonAction(-1);// <--Restart
	button = exitButton;
	button_pressed = exitButton_pressed;
	ButtonAction(0);
}

void Windows::PlayerBuildingModeWindow(Board PlayersBoard)
{
	ObjectDisplay::ImageDisplay(playerBuildingModeWindow, dstrect1);
	if (FunctionsWithArrays::isBoatLengthsArrayEmpty(PlayersBoard)) {
		button = continueButton;
		button_pressed = continueButton_pressed;
		ButtonAction(3);
	}
	displaynumbers->FindAndDisplayRightNumber(FunctionsWithArrays::AmmountOfSameLengthsInArray(PlayersBoard, 1), 123, 432); //one block ship
	displaynumbers->FindAndDisplayRightNumber(FunctionsWithArrays::AmmountOfSameLengthsInArray(PlayersBoard, 2), 123, 493); //two blocks ship
	displaynumbers->FindAndDisplayRightNumber(FunctionsWithArrays::AmmountOfSameLengthsInArray(PlayersBoard, 3), 250, 470); //three blocks ship
	displaynumbers->FindAndDisplayRightNumber(FunctionsWithArrays::AmmountOfSameLengthsInArray(PlayersBoard, 4), 365, 470); //four blocks ship
}

void Windows::ShootingModeWindow(Board BotsBoard)
{
	ObjectDisplay::ImageDisplay(shootingModeWindow, dstrect1);
	displaynumbers->FindAndDisplayRightNumber(FunctionsWithArrays::AmmountOfSameLengthsInArray(BotsBoard, 1), 123, 432); //one block ship
	displaynumbers->FindAndDisplayRightNumber(FunctionsWithArrays::AmmountOfSameLengthsInArray(BotsBoard, 2), 123, 493); //two blocks ship
	displaynumbers->FindAndDisplayRightNumber(FunctionsWithArrays::AmmountOfSameLengthsInArray(BotsBoard, 3), 318, 470); //three blocks ship
	displaynumbers->FindAndDisplayRightNumber(FunctionsWithArrays::AmmountOfSameLengthsInArray(BotsBoard, 4), 520, 470); //four blocks ship
}


void Windows::WhichBackground(Board PlayersBoard, Board BotsBoard)
{
	switch (HendleEvents::EventCode)
	{
	case 1:
		StartGameWindow();
		break;
	case 2:
		PlayerBuildingModeWindow(PlayersBoard);
		break;
	case 3:
		ShootingModeWindow(BotsBoard);
		break;
	case 4:
		PlayAgainWindow();
		break;
	case 5:
		TryAgainWindow();
		break;
	default:
		break;
	}
}

void Windows::ButtonAction(int event_type)
{
	if (button->ButtonCheck() && HendleEvents::MouseEvent == 1) {
		button_pressed->setisButtonPressedCorrect(true);
		button_pressed->DisplayButton();
	}
	else if (button->ButtonCheck() && button_pressed->getisButtonPressedCorrect() && HendleEvents::MouseEvent == 2) {
		button_pressed->DisplayButton();
	}
	else if (button->ButtonCheck() && button_pressed->getisButtonPressedCorrect() && HendleEvents::MouseEvent == 3) {
		HendleEvents::EventCode = event_type;
		button_pressed->setisButtonPressedCorrect(false);
	}
	else {
		button->DisplayButton();
		button_pressed->setisButtonPressedCorrect(false);
	}
}

