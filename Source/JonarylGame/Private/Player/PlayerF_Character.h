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


	void EndSpecialAtk();
	void SetisSpeActionA(bool isActivate = true);
	void SetisSpeActionB(bool isActivate = true);
	void SetisSpeActionX(bool isActivate = true);
	void SetisSpeActionY(bool isActivate = true);

	/// VARIABLE ///
	//MOVE
	bool GetisIdle();
	bool GetisMoving();
	bool GetisSprint();

	float GetsideMoving();
	bool GetisTimeMoving();

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
	bool GetisDamageRight();
	int GetdamageAnimNumber();

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

	/////////////////////////  SHARE INFOS ///////////////////////////
	UStates_PlayerF::EStates_PlayerF GetPlayerState();
	FStruct_CharacterStats GetPlayerStats();
};
