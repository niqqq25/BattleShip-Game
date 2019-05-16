#include "FunctionsWithArrays.h"

void FunctionsWithArrays::AddBoatLengthToArray(Board &chosenBoard, int boatLength)
{
	for (int a = 0; a < 10; a++) {
		if (chosenBoard.getBoatLengthsArrayValue(a) == -1) {
			chosenBoard.setBoatLengthArrayValue(a, boatLength);
			break;
		}
	}
}

bool FunctionsWithArrays::RemoveBoatLengthFromArray(Board &chosenBoard, int boatLength)
{
	bool isValidBoatSize = false;

	for (int a = 0; a < 10; a++) {
		if (chosenBoard.getBoatLengthsArrayValue(a) == boatLength) {
			chosenBoard.setBoatLengthArrayValue(a, -1);
			isValidBoatSize = true;
			break;
		}
	}
	return isValidBoatSize;
}

int FunctionsWithArrays::AmmountOfSameLengthsInArray(Board &chosenBoard, int searchedLength)
{
	int ammountOfLenghts = 0;
	for (int a = 0; a < 10; a++) {
		if (chosenBoard.getBoatLengthsArrayValue(a) == searchedLength) {
			ammountOfLenghts++;
		}
	}
	return ammountOfLenghts;
}

bool FunctionsWithArrays::isBoatLengthsArrayEmpty(Board &chosenBoard)
{
	for (int a = 0; a < 10; a++) {
		if (chosenBoard.getBoatLengthsArrayValue(a) != -1) {
			return false;
		}
	}
	return true;
}
