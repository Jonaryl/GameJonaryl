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
    UE_LOG(LogTemp, Log, TEXT("AScene_EnemiesManager BeginPlay()"));
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AScene_EnemiesZones::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        AScene_EnemiesZones* EnemySpawnerZone = Cast<AScene_EnemiesZones>(Actor);
        if (EnemySpawnerZone)
        {
            EnemySpawnerZone->Begin();
            allEnemiesZones.Add(EnemySpawnerZone);
        }
    }

    TArray<AActor*> FoundActorsPlayer;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerF_Character::StaticClass(), FoundActorsPlayer);
    for (AActor* Actor : FoundActorsPlayer)
    {
        PlayerCharacter = Cast<APlayerF_Character>(Actor);
    }
}
void AScene_EnemiesManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AScene_EnemiesManager::SharePlayerState(UStates_PlayerF::EStates_PlayerF playerState)
{
    CurrentPlayerState = playerState;
    for (AScene_EnemiesZones* Zone : allEnemiesZones)
    {
        if (Zone)
        {
            if(Zone->GetisActive() == true)
                Zone->SharePlayerState(playerState);
        }
    }
}



void AScene_EnemiesManager::EnemyIsDead(int id, int idZone, int idWave)
{
    for (AScene_EnemiesZones* Zone : allEnemiesZones)
    {
        if (Zone)
        {
            if(Zone->GetidZone() == idZone)
                Zone->CheckIsEnemiesDead(id, idWave);
        }
    }
}
