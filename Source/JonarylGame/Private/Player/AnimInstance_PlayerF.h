// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"

#include "Player/PlayerF_Character.h"

#include "AnimInstance_PlayerF.generated.h"

/**
 * 
 */
UCLASS()
class UAnimInstance_PlayerF : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void UpdateAnimProperties();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
		APlayerF_Character* playerClass;

	/////////////// VARIABLE ////////////////////

	///MOVE
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isMoving;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isIdle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isSprint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float sideMoving;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isTimeMoving;

	///JUMP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isJumpUp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isJumpIdle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isJumpDown;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isJumpDash;

	///DASH
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isDash;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		int dashNumber;

	//DAMAGE
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isDamaged;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isDamageRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		int damageAnimNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isCounterTake;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isRightCountered;

	///ATTACK
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		int currentHitCombo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		int AttackOneNumber;

	///SPECIAL
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isSuperMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isSpeActionA;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isSpeActionB;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isSpeActionX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isSpeActionY;

	///COUNTER
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isCounterPose;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isCounter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isRightCounter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		int counterPoseNumber;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		int counterNumber;

	/////////////// EVENT ////////////////////
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void EventAnim();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void EventCanHitTurning();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void EventRightHit();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void EventLeftHit();
};
