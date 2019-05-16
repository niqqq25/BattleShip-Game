#include "Game.h"
#include "HendleEvents.h"
#include "Board.h"
#pragma once
class PlayerActions
{
public:
	PlayerActions();
	~PlayerActions();

	void PlayerActionsController(HendleEvents &hendleevents, Board &PlayersBoard, Board &BotsBoard, bool &isPlayerTurn);
	void PlaceNewBoatOnTheBoard(HendleEvents & hendleevents, Board & PlayersBoard);
	void ShootIntoEnemiesBoats(HendleEvents &hendleevents, Board &BotsBoard, bool &isPlayerTurn);
	void BoatStartCoords(HendleEvents & hendleevents, Board & PlayersBoard);
	void BoatEndCoords(HendleEvents & hendleevents, Board & PlayersBoard);

private:
	int boatStartYCoord, boatStartXCoord, boatCurrentYCoord, boatCurrentXCoord, boatLength = 0, isTouchingAnotherShip;
	bool isContinueNewShipBuilding = false, isValidMouseClick = false;
};

