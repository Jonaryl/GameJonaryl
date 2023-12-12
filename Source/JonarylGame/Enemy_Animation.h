// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Enemy_Unit.h"

#include "Enemy_Animation.generated.h"


/**
 * 
 */
UCLASS()
class JONARYLGAME_API UEnemy_Animation : public UAnimInstance
{
	GENERATED_BODY()

public:
	UEnemy_Animation();


protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void UpdateAnimProperties();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
		AEnemy_Unit* enemyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float xMove;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float yMove;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		int currentCombo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isDamaged;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isRightAttackHit;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isCounterTake;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		int hitCountDamageAnimation;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float DmgBlendAlpha;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float DmgBlendR;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float DmgBlendL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float ArmorValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isSlowDownTake;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void CanAttackEvent();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void LaunchParticleEvent();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void EndAnimationEvent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void AttackIsRight();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void AttackIsLeft();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void EndDamage();	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void EndDamageAnimation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void ActivateSlowMode();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void StopAttackTurn();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void EndArmorDamage();
};
