#include "Board.h"
#include "ObjectDisplay.h"

Board::Board(int boardXCoord)
{
	boardBack = ObjectDisplay::texture("Pictures/board.png");
	boardCoord = ObjectDisplay::texture("Pictures/boardCoord.png");
	boardParameters.x = boardXCoord;
	boardParameters.y = 20;
	boardParameters.h = boardParameters.w = 320;
	coordParameters.h = coordParameters.w = 352;

	for (int y = 0; y < 10; y++) { // <- Makes all board empty
		for (int x = 0; x < 10; x++) {
			board[y][x] = 0;
		}
	}

	boxParameters.w = boxParameters.h = 32;
	boxWithDstredShip = ObjectDisplay::texture("Pictures/DestroyedShip.png");
	boxWithEmptyBox = ObjectDisplay::texture("Pictures/EmptyBox.png");
	boxWithShip = ObjectDisplay::texture("Pictures/BoxWithShip.png");

	AddArrayElementsToVector();
}

Board::~Board()
{
}

void Board::DrawBoard()
{
	ObjectDisplay::ImageDisplay(boardBack, boardParameters);
}

void Board::DrawBoxes(bool isEnemyBoard)
{
	for (int y = 0; y < 10; y++) { // <- Makes all board empty
		for (int x = 0; x < 10; x++) {
			boxParameters.x = x * 32 + boardParameters.x;
			boxParameters.y = y * 32 + boardParameters.y;
			if (board[y][x] == 1 && !isEnemyBoard) {
				ObjectDisplay::ImageDisplay(boxWithShip, boxParameters);
			}
			else if (board[y][x] == 2) {
				ObjectDisplay::ImageDisplay(boxWithDstredShip, boxParameters);
			}
			else if (board[y][x] == 3) {
				ObjectDisplay::ImageDisplay(boxWithEmptyBox, boxParameters);
			}
		}
	}
}

void Board::DrawCoord(int displayCoordParameters_x, int displayCoordParameters_y)
{
	coordParameters.x = displayCoordParameters_x;
	coordParameters.y = displayCoordParameters_y;
	ObjectDisplay::ImageDisplay(boardCoord, coordParameters);
}

void Board::AddArrayElementsToVector()
{
	for (int a = 0; a < 10; a++) {
		boatLengthsArray.push_back(boatLengths[a]);
	}
}

int Board::getBoardBoxValue(int boxYCoord, int boxXCoord)
{
	return board[boxYCoord][boxXCoord];
}

void Board::setBoardBoxValue(int boxYCoord, int boxXCoord, int setValue)
{
	board[boxYCoord][boxXCoord] = setValue;
}

void Board::setBoatLengthArrayValue(int arrayPlace, int setValue)
{
	boatLengthsArray[arrayPlace] = setValue;
}

SDL_Rect Board::getboardParameters()
{
	return boardParameters;
}

int Board::getBoatLengthsArrayValue(int arrayPlace)
{
	return boatLengthsArray[arrayPlace];
}

