// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/Enemies_Behaviors.h"
#include "Enemies_Unit.generated.h"

/**
 * 
 */
UCLASS()
class AEnemies_Unit : public AEnemies_Behaviors
{
	GENERATED_BODY()
	
protected:
	virtual void StopAllActions() override;

public:

	//MOVE
	bool GetisIdle();
	bool GetisMoving();
	float GetxMoving();
	float GetyMoving();

	//ATTACK
	bool GetisAttackStarted();
	int GetcurrentHitCombo();
	bool GetisAttackCombo();

	///DASH
	bool GetisDash();

	//COUNTER
	bool GetisCounterPose();
	bool GetisCounter();

	//DAMAGE
	bool GetisDamaged();
	bool GetisRightAttackHit();

	float GetDmgBlendAlpha();
	float GetDmgBlendR();
	float GetDmgBlendL();

	bool GetisSlowDownTake();

};
