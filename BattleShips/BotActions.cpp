#include "BotActions.h"
#include "FunctionsWithArrays.h"
#include "CreateAndDeleteBoat.h"
#include "HendleEvents.h"


BotActions::BotActions(Board & botboard)
{
	srand(time(NULL));
	RandomlyGenerateBoats(botboard);
}

BotActions::~BotActions()
{
}

void BotActions::RandomlyGenerateBoats(Board & botboard)
{
	bool isLegit;
	while (!FunctionsWithArrays::isBoatLengthsArrayEmpty(botboard)) {
		isLegit = true;
		RandomlyGenerateCoords();

		if (startYCoord == endYCoord && startXCoord == endXCoord) {
			if (FunctionsWithArrays::AmmountOfSameLengthsInArray(botboard, 4) == 0 && //<-- 1 length boats generates at the end
				FunctionsWithArrays::AmmountOfSameLengthsInArray(botboard, 3) == 0 &&
				FunctionsWithArrays::AmmountOfSameLengthsInArray(botboard, 2) == 0) {

				boatlength = CreateAndDeleteBoat::DrawNewBoat(&botboard, startYCoord, startXCoord, startYCoord, startXCoord, isLegit);
				if (isLegit) { FunctionsWithArrays::RemoveBoatLengthFromArray(botboard, boatlength); }
			}
		}
		else if (startXCoord == endXCoord || startYCoord == endYCoord) {// <--Checks or its line

			boatlength = CreateAndDeleteBoat::DrawNewBoat(&botboard, startYCoord, startXCoord, endYCoord, endXCoord, isLegit);
			if (isLegit) {
				if (!FunctionsWithArrays::RemoveBoatLengthFromArray(botboard, boatlength)) {
					CreateAndDeleteBoat::DestroyBoat(&botboard, startYCoord, startXCoord, 1, 0, boatlength);
				}
			}
		}
	}
}

void BotActions::ShootIntoPlayersBoats(Board & PlayersBoard, bool & isPlayerTurn)
{
	if (timer == 0) {
		timer = 0;
		boatlength = 0;
		if (!isPlayerTurn) {
			if (!isBoatHit && !isBoatDirectionKnown) { //<-- Shots randomly
				RandomlyGenerateCoords();
				MakeEndCoordsEqlToStartCoord(0, 0);
				if (PlayersBoard.getBoardBoxValue(endYCoord, endXCoord) == 0) {
					PlayersBoard.setBoardBoxValue(endYCoord, endXCoord, 3);
					isPlayerTurn = true;
				}
				else if (PlayersBoard.getBoardBoxValue(endYCoord, endXCoord) == 1) {
					PlayersBoard.setBoardBoxValue(endYCoord, endXCoord, 2);
					if (CreateAndDeleteBoat::isFullyDestroyedShip(&PlayersBoard, endYCoord, endXCoord, boatlength)) {
						FunctionsWithArrays::AddBoatLengthToArray(PlayersBoard, boatlength);
						if (FunctionsWithArrays::AmmountOfSameLengthsInArray(PlayersBoard, -1) == 0) {
							HendleEvents::EventCode = 5;
						}
					}
					isBoatHit = true;
				}
			}
			else if (isBoatHit && !isBoatDirectionKnown) { //<-- Finds direction
				if (CreateAndDeleteBoat::isCoordAboveOrToTheLeftSideOfTheBoatExist(startXCoord) && !isPlayerTurn && !isBoatDirectionKnown) {
					MakeEndCoordsEqlToStartCoord(0, -1);
					CheckOrRightDirection(PlayersBoard, 1, isPlayerTurn);
				}
				if (CreateAndDeleteBoat::isCoordAboveOrToTheLeftSideOfTheBoatExist(startYCoord) && !isPlayerTurn && !isBoatDirectionKnown) {
					MakeEndCoordsEqlToStartCoord(-1, 0);
					CheckOrRightDirection(PlayersBoard, 2, isPlayerTurn);
				}
				if (CreateAndDeleteBoat::isCoordBelowOrToTheRightSideOfTheBoatExist(startXCoord) && !isPlayerTurn && !isBoatDirectionKnown) {
					MakeEndCoordsEqlToStartCoord(0, 1);
					CheckOrRightDirection(PlayersBoard, 3, isPlayerTurn);
				}
				if (CreateAndDeleteBoat::isCoordBelowOrToTheRightSideOfTheBoatExist(startYCoord) && !isPlayerTurn && !isBoatDirectionKnown) {
					MakeEndCoordsEqlToStartCoord(1, 0);
					CheckOrRightDirection(PlayersBoard, 4, isPlayerTurn);
				}
				if (!isPlayerTurn && !isBoatDirectionKnown) { //<-- One block ship
					isBoatHit = false;
				}
			}

			if (isBoatHit && isBoatDirectionKnown && !isPlayerTurn) { //<-- Does things
				bool isRunning = true; //<-- For loop
				if (directiontType == 1) {
					while (isRunning) {
						if (endXCoord >= 0 && PlayersBoard.getBoardBoxValue(endYCoord, endXCoord) == 1) {
							PlayersBoard.setBoardBoxValue(endYCoord, endXCoord, 2);
							boatlength = 0;
							if (CreateAndDeleteBoat::isFullyDestroyedShip(&PlayersBoard, endYCoord, endXCoord, boatlength)) {
								FunctionsWithArrays::AddBoatLengthToArray(PlayersBoard, boatlength);
								if (FunctionsWithArrays::AmmountOfSameLengthsInArray(PlayersBoard, -1) == 0) {
									HendleEvents::EventCode = 5;
									break;
								}
							}
							endXCoord--;
						}
						else if (endXCoord >= 0 && PlayersBoard.getBoardBoxValue(endYCoord, endXCoord) == 0) {
							PlayersBoard.setBoardBoxValue(endYCoord, endXCoord, 3);
							isPlayerTurn = true;
							if (isValidToChangeDirection(PlayersBoard, 1)) { directiontType = 3; }
							else { isBoatHit = isBoatDirectionKnown = false; }
							isRunning = false;
						}
						else {
							if (isValidToChangeDirection(PlayersBoard, 1)) { directiontType = 3; }
							else { isBoatHit = isBoatDirectionKnown = false; }
							isRunning = false;
						}
					}
				}
				else if (directiontType == 2) {
					while (isRunning) {
						if (endYCoord >= 0 && PlayersBoard.getBoardBoxValue(endYCoord, endXCoord) == 1) {
							PlayersBoard.setBoardBoxValue(endYCoord, endXCoord, 2);
							boatlength = 0;
							if (CreateAndDeleteBoat::isFullyDestroyedShip(&PlayersBoard, endYCoord, endXCoord, boatlength)) {
								FunctionsWithArrays::AddBoatLengthToArray(PlayersBoard, boatlength);
								if (FunctionsWithArrays::AmmountOfSameLengthsInArray(PlayersBoard, -1) == 0) {
									HendleEvents::EventCode = 5;
									break;
								}
							}
							endYCoord--;
						}
						else if (endYCoord >= 0 && PlayersBoard.getBoardBoxValue(endYCoord, endXCoord) == 0) {
							PlayersBoard.setBoardBoxValue(endYCoord, endXCoord, 3);
							isPlayerTurn = true;
							if (isValidToChangeDirection(PlayersBoard, 2)) { directiontType = 4; }
							else { isBoatHit = isBoatDirectionKnown = false; }
							isRunning = false;
						}
						else {
							if (isValidToChangeDirection(PlayersBoard, 2)) { directiontType = 4; }
							else { isBoatHit = isBoatDirectionKnown = false; }
							isRunning = false;
						}
					}
				}
				else if (directiontType == 3) {
					while (isRunning) {
						if (endXCoord < 10 && PlayersBoard.getBoardBoxValue(endYCoord, endXCoord) == 1) {
							PlayersBoard.setBoardBoxValue(endYCoord, endXCoord, 2);
							boatlength = 0;
							if (CreateAndDeleteBoat::isFullyDestroyedShip(&PlayersBoard, endYCoord, endXCoord, boatlength)) {
								FunctionsWithArrays::AddBoatLengthToArray(PlayersBoard, boatlength);
								if (FunctionsWithArrays::AmmountOfSameLengthsInArray(PlayersBoard, -1) == 0) {
									HendleEvents::EventCode = 5;
									break;
								}
							}
							endXCoord++;
						}
						else if (endXCoord < 10 && PlayersBoard.getBoardBoxValue(endYCoord, endXCoord) == 0) {
							PlayersBoard.setBoardBoxValue(endYCoord, endXCoord, 3);
							isPlayerTurn = true;
							if (isValidToChangeDirection(PlayersBoard, 1)) { directiontType = 3; }
							else { isBoatHit = isBoatDirectionKnown = false; }
							isRunning = false;
						}
						else {
							if (isValidToChangeDirection(PlayersBoard, 1)) { directiontType = 3; }
							else { isBoatHit = isBoatDirectionKnown = false; }
							isRunning = false;
						}
					}
				}
				else if (directiontType == 4) {
					while (isRunning) {
						if (endYCoord < 10 && PlayersBoard.getBoardBoxValue(endYCoord, endXCoord) == 1) {
							boatlength = 0;
							if (CreateAndDeleteBoat::isFullyDestroyedShip(&PlayersBoard, endYCoord, endXCoord, boatlength)) {
								FunctionsWithArrays::AddBoatLengthToArray(PlayersBoard, boatlength);
								if (FunctionsWithArrays::AmmountOfSameLengthsInArray(PlayersBoard, -1) == 0) {
									HendleEvents::EventCode = 5;
									break;
								}
							}
							endYCoord++;
						}
						else if (endYCoord < 10 && PlayersBoard.getBoardBoxValue(endYCoord, endXCoord) == 0) {
							PlayersBoard.setBoardBoxValue(endYCoord, endXCoord, 3);
							isPlayerTurn = true;
							if (isValidToChangeDirection(PlayersBoard, 4)) { directiontType = 2; }
							else { isBoatHit = isBoatDirectionKnown = false; }
							isRunning = false;
						}
						else {
							if (isValidToChangeDirection(PlayersBoard, 4)) { directiontType = 2; }
							else { isBoatHit = isBoatDirectionKnown = false; }
							isRunning = false;
						}
					}
				}
			}
		}
	}
	else if(!isPlayerTurn) { timer++; }
}

void BotActions::MakeEndCoordsEqlToStartCoord(int yCoordDiff, int xCoordDiff)
{
	endYCoord = startYCoord + 1 * yCoordDiff;
	endXCoord = startXCoord + 1 * xCoordDiff;
}

void BotActions::CheckOrRightDirection(Board & PlayersBoard, int chosenDirection, bool & isPlayerTurn)
{
	if (PlayersBoard.getBoardBoxValue(endYCoord, endXCoord) == 0) {
		PlayersBoard.setBoardBoxValue(endYCoord, endXCoord, 3);
		isPlayerTurn = true;
	}
	else if (PlayersBoard.getBoardBoxValue(endYCoord, endXCoord) == 1) {
		isBoatDirectionKnown = true;
		directiontType = chosenDirection;
	}
}

bool BotActions::isValidToChangeDirection(Board & PlayersBoard, int currentDirection)
{
	switch (currentDirection)
	{
	case 1:
		if (CreateAndDeleteBoat::isCoordBelowOrToTheRightSideOfTheBoatExist(startXCoord) && PlayersBoard.getBoardBoxValue(startYCoord, startXCoord + 1) != 3
			&& PlayersBoard.getBoardBoxValue(startYCoord, startXCoord + 1) != 2) {
			MakeEndCoordsEqlToStartCoord(0, 1);
			return true;
		}
		break;
	case 2:
		if (CreateAndDeleteBoat::isCoordBelowOrToTheRightSideOfTheBoatExist(startYCoord && PlayersBoard.getBoardBoxValue(startYCoord + 1, startXCoord) != 3
		&& PlayersBoard.getBoardBoxValue(startYCoord + 1, startXCoord) != 2)) {
			MakeEndCoordsEqlToStartCoord(1, 0);
			return true;
		}
		break;
	case 3:
		if (CreateAndDeleteBoat::isCoordAboveOrToTheLeftSideOfTheBoatExist(startXCoord) && PlayersBoard.getBoardBoxValue(startYCoord, startXCoord - 1) != 3
			&& PlayersBoard.getBoardBoxValue(startYCoord, startXCoord - 1) != 2) {
			MakeEndCoordsEqlToStartCoord(0, -1);
			return true;
		}
		break;
	case 4:
		if (CreateAndDeleteBoat::isCoordAboveOrToTheLeftSideOfTheBoatExist(startYCoord) && PlayersBoard.getBoardBoxValue(startYCoord - 1, startXCoord) != 3
			&& PlayersBoard.getBoardBoxValue(startYCoord - 1, startXCoord) != 2) {
			MakeEndCoordsEqlToStartCoord(-1, 0);
			return true;
		}
		break;
	}
	return false;
}

void BotActions::RandomlyGenerateCoords()
{
	startYCoord = rand() % 10;
	startXCoord = rand() % 10;
	endYCoord = rand() % 10;
	endXCoord = rand() % 10;
}