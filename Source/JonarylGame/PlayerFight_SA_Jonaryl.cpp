// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_SA_Jonaryl.h"


void UPlayerFight_SA_Jonaryl::SpecialAttack()
{
	Super::SpecialAttack();
	UE_LOG(LogTemp, Warning, TEXT("SpecialAttack"));
	if (PlayerFight_Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerFight_Character SuperModeActivate"));
		PlayerFight_Character->SuperModeActivate();
	}
}


void UPlayerFight_SA_Jonaryl::GetPlayer(AActor* player)
{
	//Super::GetPlayer(player);
	PlayerFight_Character = Cast<APlayerFight_Character>(player);
}


void UPlayerFight_SA_Jonaryl::XBtnActionSpe()
{
	Super::XBtnActionSpe();
	UE_LOG(LogTemp, Warning, TEXT("XBtnActionSpe"));
	StartSlowMotion();
}
void UPlayerFight_SA_Jonaryl::YBtnActionSpe()
{
	Super::YBtnActionSpe();
	UE_LOG(LogTemp, Warning, TEXT("YBtnActionSpe"));
}
void UPlayerFight_SA_Jonaryl::BBtnActionSpe()
{
	Super::BBtnActionSpe();
	UE_LOG(LogTemp, Warning, TEXT("BBtnActionSpe"));
}
void UPlayerFight_SA_Jonaryl::ABtnActionSpe()
{
	Super::ABtnActionSpe();
	UE_LOG(LogTemp, Warning, TEXT("ABtnActionSpe")); 
	EndSlowMotion();
}


void UPlayerFight_SA_Jonaryl::StartSlowMotion() 
{
    Super::StartSlowMotion();
}
void UPlayerFight_SA_Jonaryl::EndSlowMotion() 
{
    Super::EndSlowMotion();
}




void UPlayerFight_SA_Jonaryl::RemoveAllEnemy()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy_Unit::StaticClass(), FoundActors);
	UE_LOG(LogTemp, Warning, TEXT("RemoveAllEnemy UPlayerFight_SA_Jonaryl"));
	// Destroy all enemy characters in the array
	for (AActor* Actor : FoundActors)
	{
		if (Actor && Actor->IsA<AEnemy_Unit>())
	    {
		    UE_LOG(LogTemp, Warning, TEXT("RemoveAllEnemies"));
		    Actor->Destroy();
	    }
	}
}