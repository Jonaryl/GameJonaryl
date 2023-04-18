// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerFight_Character.h"




#include "PlayerFIght_Animation.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API UPlayerFIght_Animation : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerFIght_Animation();


protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void UpdateAnimProperties();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void CanAttackEvent();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void EndCombo();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void FinalComboAttack();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void CanCounterStanceEvent();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Event")
		void EndCounterStanceEvent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
		APlayerFight_Character* playerClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		float speedMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isStartJump;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isIdleJump;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isDashJump;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isDash;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isNearGround;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isSprint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isStrongAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		int currentCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isCounterStance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isCounter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isCounterLeft;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
		bool isIdle;
	
};
