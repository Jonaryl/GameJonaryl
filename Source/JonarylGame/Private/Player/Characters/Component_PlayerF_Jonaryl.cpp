// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Characters/Component_PlayerF_Jonaryl.h"


/////////////////////////// START ///////////////////////////
void UComponent_PlayerF_Jonaryl::SpecialAttack() {}

/////////////////////////// SLOW MOTION ///////////////////////////
void UComponent_PlayerF_Jonaryl::StartSlowMotion(float slowStrength)
{
	Super::StartSlowMotion(slowStrength);
}
void UComponent_PlayerF_Jonaryl::EndSlowMotion()
{
	Super::EndSlowMotion();
}
void UComponent_PlayerF_Jonaryl::AllEnemyEndSlow()
{
	Super::AllEnemyEndSlow();
}

/////////////////////////// INPUT ///////////////////////////
void UComponent_PlayerF_Jonaryl::ABtnActionSpe() 
{
	UE_LOG(LogTemp, Warning, TEXT("ABtnActionSpe"));
	timeCurrentSpecialAtk = 0;
	isSpecialAttacking = true;
	indexParticle = 0;
}
void UComponent_PlayerF_Jonaryl::BBtnActionSpe() 
{
	UE_LOG(LogTemp, Warning, TEXT("BBtnActionSpe"));
	timeCurrentSpecialAtk = 0;
	isSpecialAttacking = true;
	indexParticle = 1;
}
void UComponent_PlayerF_Jonaryl::XBtnActionSpe() 
{
	UE_LOG(LogTemp, Warning, TEXT("XBtnActionSpe"));
	timeCurrentSpecialAtk = 0;
	isSpecialAttacking = true;
	indexParticle = 2;
}
void UComponent_PlayerF_Jonaryl::YBtnActionSpe() 
{
	UE_LOG(LogTemp, Warning, TEXT("YBtnActionSpe"));
	timeCurrentSpecialAtk = 0;
	isSpecialAttacking = true;
	indexParticle = 3;
}

/////////////////////////// TOOL ///////////////////////////
void UComponent_PlayerF_Jonaryl::GetPlayer(AActor* player) 
{
	currentPlayer = Cast<APlayerF_Character>(player);
}
