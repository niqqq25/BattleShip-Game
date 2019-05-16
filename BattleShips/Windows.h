#include "Game.h"
#include "Board.h"
#pragma once
class Windows
{
public:
	Windows();
	~Windows();

	void StartGameWindow();
	void TryAgainWindow();
	void PlayAgainWindow();
	void PlayerBuildingModeWindow(Board PlayersBoard);
	void ShootingModeWindow(Board BotsBoard);

	void WhichBackground(Board PlayersBoard, Board BotsBoard);

	void ButtonAction(int event_type);


private:

	SDL_Texture *startGameWindow, *tryAgainWindow, *playAgainWindow, *playerBuildingModeWindow, *shootingModeWindow;

	SDL_Rect dstrect, dstrect1, forBackgrounds;
};

