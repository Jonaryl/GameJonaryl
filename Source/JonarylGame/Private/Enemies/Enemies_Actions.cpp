// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemies_Actions.h"

void AEnemies_Actions::BeginPlay()
{
    Super::BeginPlay();
    for (int32 Step = 0; Step < dashMaxTurn; ++Step)
    {
        float Time = static_cast<float>(Step) / static_cast<float>(dashMaxTurn - 1);

        float T = 1 - FMath::Pow(1 - Time, dashSpeedProgression);

        float Value = FMath::Lerp(dashMaxSpeed, dashMinSpeed, T);

        DashValues.Add(Value);
    }
}

//////////////////////////// DASH /////////////////////////////
bool AEnemies_Actions::ActionDash(FVector mainVector, int actionDashTurn, FString direction, TArray<float> speed)
{
	bool isDashEnded = false;

    int numberOfElements = sizeof(speed) / sizeof(speed[0]);

    if (direction == "right")
    {
        if(isDashBack)
            isDashBack = false;
        if(isDashLeft)
            isDashLeft = false;
        if(!isDashRight)
            isDashRight = true;
    }
    else if(direction == "left")
    {
        if (isDashBack)
            isDashBack = false;
        if (!isDashLeft)
            isDashLeft = true;
        if (isDashRight)
            isDashRight = false;
    }
    else
    {
        if (!isDashBack)
            isDashBack = true;
        if (isDashLeft)
            isDashLeft = false;
        if (isDashRight)
            isDashRight = false;
    }
    canBeHit = false;

    SetActionState(EStates_EnemiesActions::Dash, 0.0f);

    if(actionDashTurn < numberOfElements)
        AddForce(mainVector, (speed[actionDashTurn] * dashForce));
    else
        AddForce(mainVector, (speed[numberOfElements-1] * dashForce));

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

