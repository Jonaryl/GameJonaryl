// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/Scene_EnemiesManager.h"

AScene_EnemiesManager::AScene_EnemiesManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void AScene_EnemiesManager::BeginPlay()
{
	Super::BeginPlay();

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemies_Unit::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        AEnemies_Unit* EnemyUnit = Cast<AEnemies_Unit>(Actor);
        if (EnemyUnit)
        {
            allEnemies.Add(EnemyUnit);
        }
    }
}
void AScene_EnemiesManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AScene_EnemiesManager::SharePlayerState(UStates_PlayerF::EStates_PlayerF playerState)
{
    UE_LOG(LogTemp, Log, TEXT("SharePlayerState = %d"), playerState);

    CurrentPlayerState = playerState;
    for (AEnemies_Unit* Component : allEnemies)
    {
        if (Component)
        {
            Component->SetPlayerState(playerState);
        }
    }
}
