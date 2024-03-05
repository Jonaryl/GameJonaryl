// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/Enemies_Behaviors.h"

#include "Structures/Struct_CharacterStats.h"
#include "Structures/Struct_DeathData.h"

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
	//////////////////////////// ANIMATION ////////////////////////////
	//MOVE
	bool GetisIdle();
	bool GetisMoving();
	bool GetisRuning();
	float GetxMoving();
	float GetyMoving();

	//ATTACK
	bool GetisAttackStarted();
	int GetcurrentHitCombo();
	bool GetisAttackCombo();

	///DASH
	bool GetisDashBack();
	bool GetisDashLeft();
	bool GetisDashRight();
	int GetdashNumber();

	//COUNTER
	bool GetisCounterPose();
	bool GetisCounter();

	//DAMAGE
	bool GetisDamaged();
	bool GetisRightAttackHit();

	int GethitCountDamageAnimation();

	float GetDmgBlendAlpha();
	float GetDmgBlendR();
	float GetDmgBlendL();

	bool GetisSlowDownTake();

	bool GetisCounterTake();

	/// EVENT ///
	void EventAnim();

	virtual void LaunchParticle() override;
	virtual void EnableDamage() override;
	virtual void CounterTake() override;
	virtual void EndSlowMode() override;

	virtual void AdvertAttack() override;

	//////////////////////////// INFORMATION ////////////////////////////
	FStruct_CharacterStats GetEnemyStats();
	bool GetisEnemyDead();
	float GetdeathAnimationCooldown();
	int GetEnemyId();

	FStruct_DeathData deathData;
	FStruct_DeathData GetDeathData();
	void SethasSendDeadMessage(bool hasSend = true);
};
