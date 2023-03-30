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
	isNearGround = playerClass->GetisNearGround();
	isIdle = playerClass->GetisIdle();
}