// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AnimInstance_PlayerF.h"

void UAnimInstance_PlayerF::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	playerClass = Cast<APlayerF_Character>(TryGetPawnOwner());
}
void UAnimInstance_PlayerF::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (playerClass)
	{
		UpdateAnimProperties();
	}
	else
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerF_Character::StaticClass(), OutActors);

		for (AActor* Actor : OutActors)
		{
			playerClass = Cast<APlayerF_Character>(Actor);
			if (playerClass)
			{
				UpdateAnimProperties();
				break;
			}
		}
	}
}

//ANIMATION UPDATE
void UAnimInstance_PlayerF::UpdateAnimProperties()
{
	//MOVE
	isMoving = playerClass->GetisMoving();
	isIdle = playerClass->GetisIdle();
	isSprint = playerClass->GetisSprint();

	sideMoving = playerClass->GetsideMoving();

	isTimeMoving = playerClass->GetisTimeMoving();

	//JUMP
	isJumpUp = playerClass->GetisJumpUp();
	isJumpIdle = playerClass->GetisJumpIdle();
	isJumpDown = playerClass->GetisJumpDown();
	isJumpDash = playerClass->GetisJumpDash();

	//DASH
	isDash = playerClass->GetisDash();
	dashNumber = playerClass->GetdashNumber();

	//DAMAGE
	isDamaged = playerClass->GetisDamaged();
	isDamageRight = playerClass->GetisDamageRight();
	damageAnimNumber = playerClass->GetdamageAnimNumber();

	//ATTACK
	isAttacking = playerClass->GetisAttacking();

	currentHitCombo = playerClass->GetcurrentHitCombo();
	AttackOneNumber = playerClass->GetAttackOneNumber();

	//SPECIAL
	isSuperMode = playerClass->GetisSuperMode();

	isSpeActionA = playerClass->GetisSpeActionA();
	isSpeActionB = playerClass->GetisSpeActionB();
	isSpeActionX = playerClass->GetisSpeActionX();
	isSpeActionY = playerClass->GetisSpeActionY();

	//COUNTER
	isCounterPose = playerClass->GetisCounterPose();
	isCounter = playerClass->GetisCounter();
	isRightCounter = playerClass->GetisRightCounter();

	counterPoseNumber = playerClass->GetcounterPoseNumber();
	counterNumber = playerClass->GetcounterNumber();

}

//EVENTS
void UAnimInstance_PlayerF::EventAnim_Implementation()
{
	playerClass->EventAnim();
}