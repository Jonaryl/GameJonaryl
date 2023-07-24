// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFIght_Animation.h"

UPlayerFIght_Animation::UPlayerFIght_Animation()
{

}

void UPlayerFIght_Animation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	playerClass = Cast<APlayerFight_Character>(TryGetPawnOwner());	
}

void UPlayerFIght_Animation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (playerClass)
	{
		UpdateAnimProperties();
	}
	else
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerFight_Character::StaticClass(), OutActors); 

		for (AActor* Actor : OutActors)
		{
			playerClass = Cast<APlayerFight_Character>(Actor);
			if (playerClass)
			{
				UpdateAnimProperties();
				break;
			}
		}
	}
}

void UPlayerFIght_Animation::UpdateAnimProperties()
{
	speedMove = playerClass->GetSpeed();
	isStartJump = playerClass->GetisStartJump();
	isIdleJump = playerClass->GetisIdleJump();
	isDashJump = playerClass->GetisDashJump();
	isDash = playerClass->GetisDash();
	dashNumber = playerClass->GetdashNumber();
	isNearGround = playerClass->GetisNearGround();
	isIdle = playerClass->GetisIdle();
	isSprint = playerClass->GetisSprint();
	isAttacking = playerClass->GetisAttacking();
	isStrongAttacking = playerClass->GetisStrongAttacking();
	currentCombo = playerClass->GetcurrentCombo();
	AttackOneNumber = playerClass->GetAttackOneNumber();

	isCounterStance = playerClass->GetisCounterStance();
	isCounter = playerClass->GetisCounter();
	isCounterLeft = playerClass->GetisCounterLeft();
	isRightAttack = playerClass->GetisDamageRight();
	isDamaged = playerClass->GetisDamaged();

	//UE_LOG(LogTemp, Warning, TEXT(" UpdateAnimProperties isCounterStance = %s"), isCounterStance ? TEXT("True") : TEXT("False"));
	}


void UPlayerFIght_Animation::CanAttackEvent_Implementation()
{
	playerClass->CanAttack();
}
void UPlayerFIght_Animation::EndCombo_Implementation()
{
	playerClass->EndCombo();
}
void UPlayerFIght_Animation::FinalComboAttack_Implementation()
{
	playerClass->FinalComboAttack();
}
void UPlayerFIght_Animation::CanCounterStanceEvent_Implementation()
{
	playerClass->CanCounterStance();
}
void UPlayerFIght_Animation::EndCounterStanceEvent_Implementation()
{
	playerClass->EndCounterStance();
}
void UPlayerFIght_Animation::HitCountEvent_Implementation()
{
	playerClass->HitCount();
}