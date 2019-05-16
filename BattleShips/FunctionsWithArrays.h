#include "Game.h"
#include "Board.h"
#pragma once
class FunctionsWithArrays
{
public:
	static void AddBoatLengthToArray(Board &chosenBoard,  int boatLength);
	static bool RemoveBoatLengthFromArray(Board &chosenBoard, int boatLength);
	static int AmmountOfSameLengthsInArray(Board &chosenBoard, int searchedLength);
	static bool isBoatLengthsArrayEmpty(Board &chosenBoard);
};

