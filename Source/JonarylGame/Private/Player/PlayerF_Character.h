// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerF_Attack.h"
#include "PlayerF_Character.generated.h"

/**
 * 
 */
UCLASS()
class APlayerF_Character : public APlayerF_Attack
{
	GENERATED_BODY()


public:
	/////////////////////////  ANIMATION ///////////////////////////
	/// METHOD
	virtual void NeutralAction() override;
	virtual void EndAllActionAnim() override;
	virtual void EndPartialAction() override;
	virtual void StopMovingAnim() override;

	/// VARIABLE ///
	//MOVE
	bool GetisIdle();
	bool GetisMoving();
	bool GetisSprint();

	float GetsideMoving();

	//JUMP
	bool GetisJumpUp();
	bool GetisJumpIdle();
	bool GetisJumpDown();
	bool GetisJumpDash();

	//DASH
	bool GetisDash();

	int GetdashNumber();

	//DAMAGE
	bool GetisDamaged();

	//ATTACK
	bool GetisAttacking();

	int GetcurrentHitCombo();
	int GetAttackOneNumber();

	//SPECIAL
	bool GetisSuperMode();

	bool GetisSpeActionA();
	bool GetisSpeActionB();
	bool GetisSpeActionX();
	bool GetisSpeActionY();

	//COUNTER
	bool GetisCounterPose();
	bool GetisCounter();
	bool GetisRightCounter();

	int GetcounterPoseNumber();
	int GetcounterNumber();



	/// EVENT ///
	void EventAnim();
	
};
