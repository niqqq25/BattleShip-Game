#include "Game.h"
#include "Board.h"
#include "time.h"
#include "stdlib.h"
#pragma once
class BotActions
{
public:
	BotActions(Board &botboard);
	~BotActions();
	void RandomlyGenerateBoats(Board &botboard);
	void ShootIntoPlayersBoats(Board & PlayersBoard, bool & isPlayerTurn);
	void MakeEndCoordsEqlToStartCoord(int yCoordDiff, int xCoordDiff);
	void CheckOrRightDirection(Board & PlayersBoard, int chosenDirection, bool & isPlayerTurn);
	bool isValidToChangeDirection(Board & PlayersBoard, int currentDirection);

	void RandomlyGenerateCoords();


private:
	bool isBoatHit = false, isBoatDirectionKnown = false;
	int boatlength, startXCoord, startYCoord, endXCoord, endYCoord, directiontType, timer = 0;
};

