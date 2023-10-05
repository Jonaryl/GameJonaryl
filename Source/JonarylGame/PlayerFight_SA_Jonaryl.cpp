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
	if (PlayerFight_Character)
		PlayerFight_Character->SetAttackSpeY(false, true, false);
	UE_LOG(LogTemp, Warning, TEXT("XBtnActionSpe"));
}
void UPlayerFight_SA_Jonaryl::YBtnActionSpe()
{
	Super::YBtnActionSpe();
	if (PlayerFight_Character)
		PlayerFight_Character->SetAttackSpeY(false, false, true);
	UE_LOG(LogTemp, Warning, TEXT("YBtnActionSpe"));
}
void UPlayerFight_SA_Jonaryl::BBtnActionSpe()
{
	Super::BBtnActionSpe();
	if (PlayerFight_Character)
		PlayerFight_Character->SetAttackSpeY(true, false, false);
	UE_LOG(LogTemp, Warning, TEXT("BBtnActionSpe"));
}
void UPlayerFight_SA_Jonaryl::ABtnActionSpe()
{
	Super::ABtnActionSpe();
	UE_LOG(LogTemp, Warning, TEXT("ABtnActionSpe")); 
	if (PlayerFight_Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerFight_Character SuperMode  DesActivate"));
		PlayerFight_Character->SuperModeActivate();
		AllEnemyEndSlow();
	}
}


void UPlayerFight_SA_Jonaryl::StartSlowMotion(float slowStrength)
{
    Super::StartSlowMotion(slowStrength);
}
void UPlayerFight_SA_Jonaryl::EndSlowMotion() 
{
    Super::EndSlowMotion();
}



void UPlayerFight_SA_Jonaryl::AllEnemyEndSlow()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy_Unit::StaticClass(), FoundActors);
	UE_LOG(LogTemp, Warning, TEXT("Calling CustomMethodToCall on AEnemy_Unit"));

	// Call the custom method on each AEnemy_Unit actor
	for (AActor* Actor : FoundActors)
	{
		AEnemy_Unit* EnemyUnit = Cast<AEnemy_Unit>(Actor);
		if (EnemyUnit)
		{
			UE_LOG(LogTemp, Warning, TEXT("Calling CustomMethodToCall for Actor %s"), *Actor->GetName());
			// Call the custom method on AEnemy_Unit
			EnemyUnit->EndSlowMode();
		}
	}
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