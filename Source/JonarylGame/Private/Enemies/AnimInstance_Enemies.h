// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "Enemies/Enemies_Unit.h"

#include "AnimInstance_Enemies.generated.h"

/**
 * 
 */
UCLASS()
class UAnimInstance_Enemies : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void UpdateAnimProperties();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
		AEnemies_Unit* enemyClass;

	/////////////// VARIABLE ////////////////////
	//MOVE
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isIdle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isMoving;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float xValueMove;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float yValueMove;

	//ATTACK
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isAttackStarted;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		int currentHitCombo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isAttackCombo;

	///DASH
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isDash;

	//COUNTER
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isCounterPose;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isCounter;

	//DAMAGE
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isDamaged;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isRightAttackHit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float DmgBlendAlpha;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float DmgBlendR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float DmgBlendL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isSlowDownTake;



};
