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


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void CanAttackEvent();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void LaunchParticleEvent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void AttackIsRight();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void AttackIsLeft();
};
