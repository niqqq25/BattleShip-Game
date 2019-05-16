#include "CreateAndDeleteBoat.h"

int CreateAndDeleteBoat::DrawNewBoat(Board * board, int startYCoord, int startXCoord, int currentYCoord, int currentXCoord, bool  &isContinueNewShipBuilding)
{
	int boatLength = sqrt((currentXCoord - startXCoord) * (currentXCoord - startXCoord) + (currentYCoord - startYCoord) * (currentYCoord - startYCoord)) + 1;

	if (boatLength <= 4) {
		if (startYCoord <= currentYCoord && startXCoord == currentXCoord) {
			isContinueNewShipBuilding = isDrawBoatValid_constXCoord(board, startYCoord, currentYCoord, startXCoord);

			while ((startYCoord <= currentYCoord) && isContinueNewShipBuilding) {
				board->setBoardBoxValue(startYCoord, startXCoord, 1);
				startYCoord++;
			}
		}
		else if (startYCoord > currentYCoord && startXCoord == currentXCoord) {
			isContinueNewShipBuilding = isDrawBoatValid_constXCoord(board, currentYCoord, startYCoord, startXCoord);

			while ((currentYCoord <= startYCoord) && isContinueNewShipBuilding) {
				board->setBoardBoxValue(currentYCoord, startXCoord, 1);
				currentYCoord++;
			}
		}
		else if (startXCoord < currentXCoord && startYCoord == currentYCoord) {
			isContinueNewShipBuilding = isDrawBoatValid_constYCoord(board, startXCoord, currentXCoord, startYCoord);

			while ((startXCoord <= currentXCoord) && isContinueNewShipBuilding) {
				board->setBoardBoxValue(startYCoord, startXCoord, 1);
				startXCoord++;
			}
		}
		else if (startXCoord > currentXCoord && startYCoord == currentYCoord) {
			isContinueNewShipBuilding = isDrawBoatValid_constYCoord(board, currentXCoord, startXCoord, startYCoord);

			while ((currentXCoord <= startXCoord) && isContinueNewShipBuilding) {
				board->setBoardBoxValue(startYCoord, currentXCoord, 1);
				currentXCoord++;
			}
		}
		else { isContinueNewShipBuilding = false; }
	}
	else {
		isContinueNewShipBuilding = false;
		boatLength = 0;
	}
	return boatLength;
}

bool CreateAndDeleteBoat::isFullyDestroyedShip(Board * board, int startYCoord, int startXCoord, int & boatLength)
{
	bool isFullyDestroyedShip = true;
	CheckOrBoatIsFullyDestroyed(board, startYCoord, startXCoord, isFullyDestroyedShip, boatLength);
	if (!isFullyDestroyedShip) {
		DestroyBoat(board, startYCoord, startXCoord, 4, 2, boatLength);
	}
	else {
		FullyDestroyBoat(board, startYCoord, startXCoord);
	}
	return isFullyDestroyedShip;
}

void CreateAndDeleteBoat::DestroyBoat(Board *board, int startYCoord, int startXCoord, int prvsValue, int newValue, int & boatLength)
{
	if (board->getBoardBoxValue(startYCoord, startXCoord) != 0) {

		board->setBoardBoxValue(startYCoord, startXCoord, newValue);

		boatLength++;

		if (startXCoord + 1 < 10) {
			if (board->getBoardBoxValue(startYCoord, startXCoord + 1) == prvsValue) { DestroyBoat(board, startYCoord, startXCoord + 1, prvsValue, newValue, boatLength); }
		}
		if (startXCoord - 1 >= 0) {
			if (board->getBoardBoxValue(startYCoord, startXCoord - 1) == prvsValue) { DestroyBoat(board, startYCoord, startXCoord - 1, prvsValue, newValue, boatLength); }
		}
		if (startYCoord + 1 < 10) {
			if (board->getBoardBoxValue(startYCoord + 1, startXCoord) == prvsValue) { DestroyBoat(board, startYCoord + 1, startXCoord, prvsValue, newValue, boatLength); }
		}
		if (startYCoord - 1 >= 0) {
			if (board->getBoardBoxValue(startYCoord - 1, startXCoord) == prvsValue) { DestroyBoat(board, startYCoord - 1, startXCoord, prvsValue, newValue, boatLength); }
		}
	}
}

void CreateAndDeleteBoat::FullyDestroyBoat(Board * board, int startYCoord, int startXCoord)
{
	board->setBoardBoxValue(startYCoord, startXCoord, 2);

	if (startXCoord + 1 < 10) {
		if (board->getBoardBoxValue(startYCoord, startXCoord + 1) == 4) { FullyDestroyBoat(board, startYCoord, startXCoord + 1); }
		else if (board->getBoardBoxValue(startYCoord, startXCoord + 1) == 0) { board->setBoardBoxValue(startYCoord, startXCoord + 1, 3); }
	}
	if (startXCoord - 1 >= 0) {
		if (board->getBoardBoxValue(startYCoord, startXCoord - 1) == 4) { FullyDestroyBoat(board, startYCoord, startXCoord - 1); }
		else if (board->getBoardBoxValue(startYCoord, startXCoord - 1) == 0) { board->setBoardBoxValue(startYCoord, startXCoord - 1, 3); }
	}
	if (startYCoord + 1 < 10) {
		if (board->getBoardBoxValue(startYCoord + 1, startXCoord) == 4) { FullyDestroyBoat(board, startYCoord + 1, startXCoord); }
		else if (board->getBoardBoxValue(startYCoord + 1, startXCoord) == 0) { board->setBoardBoxValue(startYCoord + 1, startXCoord, 3); }
	}
	if (startYCoord - 1 >= 0) {
		if (board->getBoardBoxValue(startYCoord - 1, startXCoord) == 4) { FullyDestroyBoat(board, startYCoord - 1, startXCoord); }
		else if (board->getBoardBoxValue(startYCoord - 1, startXCoord) == 0) { board->setBoardBoxValue(startYCoord - 1, startXCoord, 3); }
	}
	if (startXCoord - 1 >= 0 && startYCoord - 1 >= 0) {
		if (board->getBoardBoxValue(startYCoord - 1, startXCoord - 1) == 0) { board->setBoardBoxValue(startYCoord - 1, startXCoord - 1, 3); }
	}
	if (startXCoord + 1 < 10 && startYCoord - 1 >= 0) {
		if (board->getBoardBoxValue(startYCoord - 1, startXCoord + 1) == 0) { board->setBoardBoxValue(startYCoord - 1, startXCoord + 1, 3); }
	}
	if (startXCoord - 1 >= 0 && startYCoord + 1 < 10) {
		if (board->getBoardBoxValue(startYCoord + 1, startXCoord - 1) == 0) { board->setBoardBoxValue(startYCoord + 1, startXCoord - 1, 3); }
	}
	if (startXCoord + 1 < 10 && startYCoord + 1 < 10) {
		if (board->getBoardBoxValue(startYCoord + 1, startXCoord + 1) == 0) { board->setBoardBoxValue(startYCoord + 1, startXCoord + 1, 3); }
	}
}

void CreateAndDeleteBoat::CheckOrBoatIsFullyDestroyed(Board * board, int startYCoord, int startXCoord, bool & isFullyDestroyedShip, int & boatLength)
{
	board->setBoardBoxValue(startYCoord, startXCoord, 4);
	boatLength++;

	if (startXCoord + 1 < 10) {
		if (board->getBoardBoxValue(startYCoord, startXCoord + 1) == 2) { CheckOrBoatIsFullyDestroyed(board, startYCoord, startXCoord + 1, isFullyDestroyedShip, boatLength); }
		else if (board->getBoardBoxValue(startYCoord, startXCoord + 1) == 1) { isFullyDestroyedShip = false; }
	}
	if (startXCoord - 1 >= 0) {
		if (board->getBoardBoxValue(startYCoord, startXCoord - 1) == 2) { CheckOrBoatIsFullyDestroyed(board, startYCoord, startXCoord - 1, isFullyDestroyedShip, boatLength); }
		else if (board->getBoardBoxValue(startYCoord, startXCoord - 1) == 1) { isFullyDestroyedShip = false; }
	}
	if (startYCoord + 1 < 10) {
		if (board->getBoardBoxValue(startYCoord + 1, startXCoord) == 2) { CheckOrBoatIsFullyDestroyed(board, startYCoord + 1, startXCoord, isFullyDestroyedShip, boatLength); }
		else if (board->getBoardBoxValue(startYCoord + 1, startXCoord) == 1) { isFullyDestroyedShip = false; }
	}
	if (startYCoord - 1 >= 0) {
		if (board->getBoardBoxValue(startYCoord - 1, startXCoord) == 2) { CheckOrBoatIsFullyDestroyed(board, startYCoord - 1, startXCoord, isFullyDestroyedShip, boatLength); }
		else if (board->getBoardBoxValue(startYCoord - 1, startXCoord) == 1) { isFullyDestroyedShip = false; }
	}
}

bool CreateAndDeleteBoat::isDrawBoatValid_constXCoord(Board * board, int boatLeastYCoord, int boatMostYCoord, int constXCoord)
{
	bool isBuildBoatValid = true;

	if (isCoordAboveOrToTheLeftSideOfTheBoatExist(boatLeastYCoord)) {
		if (!isBoatRightAndLeftSideValid(board, boatLeastYCoord - 1, constXCoord)) { isBuildBoatValid = false; }
	}
	if (isCoordBelowOrToTheRightSideOfTheBoatExist(boatMostYCoord)) {
		if (!isBoatRightAndLeftSideValid(board, boatMostYCoord + 1, constXCoord)) { isBuildBoatValid = false; }
	}
	for (int leastYCoord = boatLeastYCoord; leastYCoord <= boatMostYCoord; leastYCoord++) {
		if (!isBoatRightAndLeftSideValid(board, leastYCoord, constXCoord)) { isBuildBoatValid = false; }
	}

	return isBuildBoatValid;
}

bool CreateAndDeleteBoat::isDrawBoatValid_constYCoord(Board * board, int boatLeastXCoord, int boatMostXCoord, int constYCoord)
{
	bool isBuildBoatValid = true;

	if (isCoordAboveOrToTheLeftSideOfTheBoatExist(boatLeastXCoord)) {
		if (!isBoatDownAndUpSideValid(board, constYCoord, boatLeastXCoord - 1)) { isBuildBoatValid = false; }
	}
	if (isCoordBelowOrToTheRightSideOfTheBoatExist(boatMostXCoord)) {
		if (!isBoatDownAndUpSideValid(board, constYCoord, boatMostXCoord + 1)) { isBuildBoatValid = false; }
	}
	for (int leastXCoord = boatLeastXCoord; leastXCoord <= boatMostXCoord; leastXCoord++) {
		if (!isBoatDownAndUpSideValid(board, constYCoord, leastXCoord)) { isBuildBoatValid = false; }
	}

	return isBuildBoatValid;
}

bool CreateAndDeleteBoat::isBoatDownAndUpSideValid(Board * board, int constYCoord, int boatXCoord)
{
	bool isValid = true;
	
	if((board->getBoardBoxValue(constYCoord, boatXCoord) == 1)) { isValid = false; }
	if (isCoordAboveOrToTheLeftSideOfTheBoatExist(constYCoord)) {
		if (board->getBoardBoxValue(constYCoord - 1, boatXCoord) == 1) { isValid = false; }
	}
	if (isCoordBelowOrToTheRightSideOfTheBoatExist(constYCoord)) {
		if (board->getBoardBoxValue(constYCoord + 1, boatXCoord) == 1) { isValid = false; }
	}
	
	return isValid;
}

bool CreateAndDeleteBoat::isBoatRightAndLeftSideValid(Board * board, int boatYCoord, int constXCoord)
{
	bool isValid = true;

	if ((board->getBoardBoxValue(boatYCoord, constXCoord) == 1)) { isValid = false; }
	if (isCoordAboveOrToTheLeftSideOfTheBoatExist(constXCoord)) {
		if (board->getBoardBoxValue(boatYCoord, constXCoord - 1) == 1) { isValid = false; }
	}
	if (isCoordBelowOrToTheRightSideOfTheBoatExist(constXCoord)) {
		if (board->getBoardBoxValue(boatYCoord, constXCoord + 1) == 1) { isValid = false; }
	}

	return isValid;
}

bool CreateAndDeleteBoat::isCoordAboveOrToTheLeftSideOfTheBoatExist(int boatLeastYorXCoord)
{
	bool isExist = false;

	if (boatLeastYorXCoord - 1 >= 0) {
		isExist = true;
	}

	return isExist;
}

bool CreateAndDeleteBoat::isCoordBelowOrToTheRightSideOfTheBoatExist(int boatMostYorXCoord)
{
	bool isExist = false;

	if (boatMostYorXCoord + 1 < 10) {
		isExist = true;
	}

	return isExist;
}
