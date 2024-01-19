// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemies_Actions.h"

//////////////////////////// DASH /////////////////////////////
bool AEnemies_Actions::ActionDash(FVector mainVector, int actionDashTurn)
{
	bool isDashEnded = false;

    int speed[60]{
        4000, 3000, 2000, 2000, 1600, 1300, 1000, 800, 600, 400,
        320, 320, 320, 280, 280, 250, 250, 100, 100, 100,
        80, 80, 80, 15, 15, 15, 15, 15, 15,  15,
        15, 15, 15, 15, 15, 15, 15, 15, 15,  15,
        15, 15, 15, 15, 15, 15, 15, 15, 15,  15,
        15, 15, 15, 15, 15, 15, 15, 15, 15,  15,
    };

    int numberOfElements = sizeof(speed) / sizeof(speed[0]);

    isDash = true;
    SetActionState(UStates_EnemiesActions::EStates_EnemiesActions::Dash, 0.0f);

    if(actionDashTurn < numberOfElements)
        AddForce(mainVector, speed[actionDashTurn]);

	if(actionDashTurn >= dashMaxTurn)
		isDashEnded = true;
	return isDashEnded;
}








//////////////////////////// ADD FORCE /////////////////////////////
void AEnemies_Actions::AddForce(FVector mainVector, int speed)
{
    FVector AppliedForce = GetActorLocation() + ((mainVector * speed * GetWorld()->DeltaTimeSeconds));
    SetActorLocation(AppliedForce);
}

