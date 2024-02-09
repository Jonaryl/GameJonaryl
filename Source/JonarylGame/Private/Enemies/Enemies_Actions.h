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


	//////////////////////////// DASH /////////////////////////////
	///// DASH VARIABLE //////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
		int dashMaxTurn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
		float dashForce;

	bool canBeHit;
	bool canDodge;

	////////////// DASH ANIMATION VARIABLE /////////////
	bool isDash;

	///// DASH METHOD //////
	virtual bool ActionDash(FVector mainVector, int actionDashTurn);

	//////////////////////////// ADD FORCE /////////////////////////////
	void AddForce(FVector mainVector, int speed);
	
};
