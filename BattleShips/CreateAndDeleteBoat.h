#include "Game.h"
#include "Board.h"
#pragma once
class CreateAndDeleteBoat
{
public:
	static int DrawNewBoat(Board *board, int startYCoord, int startXCoord, int currentYCoord, int currentXCoord, bool &isContinueNewShipBuilding);
	static bool isFullyDestroyedShip(Board *board, int startYCoord, int startXCoord, int &boatLength);

	static void DestroyBoat(Board *board, int startYCoord, int startXCoord, int prvsValue, int newValueint, int &boatLength);
	static void FullyDestroyBoat(Board *board, int startYCoord, int startXCoord);
	static void CheckOrBoatIsFullyDestroyed(Board *board, int startYCoord, int startXCoord, bool & isFullyDestroyedShip, int &boatLength);

	static bool isDrawBoatValid_constXCoord(Board *board, int boatLeastYCoord, int boatMostYCoord, int constXCoord);
	static bool isDrawBoatValid_constYCoord(Board *board, int boatLeastXCoord, int boatMostXCoord, int constYCoord);

	static bool isBoatDownAndUpSideValid(Board *board, int constYCoord, int boatXCoord);
	static bool isBoatRightAndLeftSideValid(Board *board, int boatYCoord, int constXCoord);

	static bool isCoordAboveOrToTheLeftSideOfTheBoatExist(int boatLeastYorXCoord);
	static bool isCoordBelowOrToTheRightSideOfTheBoatExist(int boatMostYorXCoord);
};
