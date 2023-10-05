// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_SpecialAttack.h"



// Sets default values for this component's properties
UPlayerFight_SpecialAttack::UPlayerFight_SpecialAttack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerFight_SpecialAttack::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



void UPlayerFight_SpecialAttack::SpecialAttack(){}
void UPlayerFight_SpecialAttack::XBtnActionSpe(){}
void UPlayerFight_SpecialAttack::YBtnActionSpe(){}
void UPlayerFight_SpecialAttack::BBtnActionSpe(){}
void UPlayerFight_SpecialAttack::ABtnActionSpe(){}


void UPlayerFight_SpecialAttack::GetPlayer(AActor* player)
{
}


void UPlayerFight_SpecialAttack::StartSlowMotion(float slowStrength)
{
	UWorld* World = this->GetWorld();
	AWorldSettings* WorldSettings = World->GetWorldSettings();
	if (WorldSettings)
	{
		WorldSettings->SetTimeDilation(slowStrength);
	}
}
void UPlayerFight_SpecialAttack::EndSlowMotion()
{
	UWorld* World = this->GetWorld();
	AWorldSettings* WorldSettings = World->GetWorldSettings();
	if (WorldSettings)
	{
		WorldSettings->SetTimeDilation(1.0f);
	}
}

// Called every frame
void UPlayerFight_SpecialAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UPlayerFight_SpecialAttack::AllEnemyEndSlow(){}
void UPlayerFight_SpecialAttack::RemoveAllEnemy(){}