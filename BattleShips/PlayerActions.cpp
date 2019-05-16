#include "PlayerActions.h"
#include "CreateAndDeleteBoat.h"
#include "FunctionsWithArrays.h"


PlayerActions::PlayerActions(){}

PlayerActions::~PlayerActions(){}

void PlayerActions::PlayerActionsController(HendleEvents & hendleevents, Board & PlayersBoard, Board &BotsBoard, bool &isPlayerTurn) //<--All player actions
{
	if (HendleEvents::EventCode == 2) { PlaceNewBoatOnTheBoard(hendleevents, PlayersBoard); }
	else if(isPlayerTurn && HendleEvents::EventCode == 3){
		ShootIntoEnemiesBoats(hendleevents, BotsBoard, isPlayerTurn);
	} 
}

void PlayerActions::PlaceNewBoatOnTheBoard(HendleEvents & hendleevents, Board & PlayersBoard)
{
	BoatStartCoords(hendleevents, PlayersBoard);
	BoatEndCoords(hendleevents, PlayersBoard);
	if (hendleevents.MouseEvent == 3 && isContinueNewShipBuilding) {
		if (!FunctionsWithArrays::RemoveBoatLengthFromArray(PlayersBoard, boatLength)) {
			CreateAndDeleteBoat::DestroyBoat(&PlayersBoard, boatStartYCoord, boatCurrentXCoord, 1, 0, boatLength);
		}
		isContinueNewShipBuilding = false;
	}
}

void PlayerActions::ShootIntoEnemiesBoats(HendleEvents & hendleevents, Board & BotsBoard, bool & isPlayerTurn)
{
	if (hendleevents.MouseEvent == 1 && hendleevents.isClickedOnRihtField(BotsBoard.getboardParameters())) {
		hendleevents.ConvertMousePosToBoardCoord(boatCurrentYCoord, boatCurrentXCoord, BotsBoard.getboardParameters());
		if (BotsBoard.getBoardBoxValue(boatCurrentYCoord, boatCurrentXCoord) == 0) { //<--Missed
			BotsBoard.setBoardBoxValue(boatCurrentYCoord, boatCurrentXCoord, 3);
			isPlayerTurn = false;
		}
		else if (BotsBoard.getBoardBoxValue(boatCurrentYCoord, boatCurrentXCoord) == 1) { //<-- Hit boat
			BotsBoard.setBoardBoxValue(boatCurrentYCoord, boatCurrentXCoord, 2);
			boatLength = 0;
			if (CreateAndDeleteBoat::isFullyDestroyedShip(&BotsBoard, boatCurrentYCoord, boatCurrentXCoord, boatLength)) {
				FunctionsWithArrays::AddBoatLengthToArray(BotsBoard, boatLength);
				if (FunctionsWithArrays::AmmountOfSameLengthsInArray(BotsBoard, -1) == 0) {
					HendleEvents::EventCode = 4;
				}
			}
		}
	}
}

void PlayerActions::BoatStartCoords(HendleEvents & hendleevents, Board & PlayersBoard)
{
	if (hendleevents.MouseEvent == 1 && hendleevents.isClickedOnRihtField(PlayersBoard.getboardParameters())) {
		isContinueNewShipBuilding = true;
		hendleevents.ConvertMousePosToBoardCoord(boatCurrentYCoord, boatCurrentXCoord, PlayersBoard.getboardParameters());
		boatStartXCoord = boatCurrentXCoord;
		boatStartYCoord = boatCurrentYCoord;
		if (PlayersBoard.getBoardBoxValue(boatStartYCoord, boatStartXCoord) == 1) { //<-- Deletes ship
			boatLength = 0;
			CreateAndDeleteBoat::DestroyBoat(&PlayersBoard, boatStartYCoord, boatStartXCoord, 1, 0, boatLength);
			FunctionsWithArrays::AddBoatLengthToArray(PlayersBoard, boatLength);
			boatLength = 0;
			isContinueNewShipBuilding = false;
		}
	}
}

void PlayerActions::BoatEndCoords(HendleEvents & hendleevents, Board & PlayersBoard)
{
	if (hendleevents.MouseEvent == 2 && hendleevents.isClickedOnRihtField(PlayersBoard.getboardParameters()) && isContinueNewShipBuilding) {
		hendleevents.ConvertMousePosToBoardCoord(boatCurrentYCoord, boatCurrentXCoord, PlayersBoard.getboardParameters());
		CreateAndDeleteBoat::DestroyBoat(&PlayersBoard, boatStartYCoord, boatStartXCoord, 1, 0, boatLength);
		boatLength = CreateAndDeleteBoat::DrawNewBoat(&PlayersBoard, boatStartYCoord, boatStartXCoord, boatCurrentYCoord, boatCurrentXCoord, isContinueNewShipBuilding);
		if (!isContinueNewShipBuilding) {
			CreateAndDeleteBoat::DestroyBoat(&PlayersBoard, boatStartYCoord, boatStartXCoord, 1, 0, boatLength);
		}
	}
}