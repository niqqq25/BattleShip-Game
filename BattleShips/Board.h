#include "Game.h"
#pragma once

class Board
{
public:
	Board(int boardXCoord);
	~Board();

	void DrawBoard();
	void DrawBoxes(bool isEnemyBoard);
	void DrawCoord(int displayCoordParameters_x, int displayCoordParameters_y);
	void AddArrayElementsToVector();

	int getBoardBoxValue(int boxYCoord, int boxXCoord);
	SDL_Rect getboardParameters();
	int getBoatLengthsArrayValue(int arrayPlace);
	void setBoardBoxValue(int boxYCoord, int boxXCoord, int setValue);
	void setBoatLengthArrayValue(int arrayPlace, int setValue);

private:
	int boatLengths[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
	vector <int> boatLengthsArray;
	int board[10][10];
	SDL_Texture *boardBack, *boxWithShip, *boxWithDstredShip, *boxWithEmptyBox, *boxWithNewShip, *boardCoord;
	SDL_Rect boardParameters, boxParameters, coordParameters;
};

