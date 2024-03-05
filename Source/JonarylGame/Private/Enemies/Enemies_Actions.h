// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/Enemies_Move.h"
#include "Enemies_Actions.generated.h"

/**
 * 
 */
UCLASS()
class AEnemies_Actions : public AEnemies_Move
{
	GENERATED_BODY()

protected:
	/////////////////////////// BASE METHOD ///////////////////////////
	virtual void BeginPlay() override;

	//////////////////////////// DASH /////////////////////////////
	///// DASH VARIABLE //////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
		int dashMaxTurn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
		int dashMaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
		int dashMinSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
		int dashSpeedProgression;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
		float dashForce;

	bool canBeHit;
	bool canDodge;

	TArray<float> DashValues;

	////////////// DASH ANIMATION VARIABLE /////////////
	bool isDashBack;
	bool isDashLeft;
	bool isDashRight;
	int dashNumber;

	///// DASH METHOD //////
	virtual bool ActionDash(FVector mainVector, int actionDashTurn, FString direction, TArray<float> speed);

	//////////////////////////// ADD FORCE /////////////////////////////
	void AddForce(FVector mainVector, int speed);
	
};
