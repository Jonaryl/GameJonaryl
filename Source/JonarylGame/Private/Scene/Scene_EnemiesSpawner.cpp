// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene/Scene_EnemiesSpawner.h"


void AScene_EnemiesSpawner::SpawnEnemy()
{
	if (EnemyClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.OverrideLevel = GetLevel();
		SpawnParams.ObjectFlags |= RF_Transient;

		FVector SpawnLocation = GetActorLocation() + FMath::RandPointInBox(GetComponentsBoundingBox());
		FRotator SpawnRotation;

		SpawnedEnemy = GetWorld()->SpawnActor<AEnemies_Unit>(EnemyClass, SpawnLocation, SpawnRotation, SpawnParams);
		SpawnedEnemy->SetIds(id, idZone, idWave);
	}
}

void AScene_EnemiesSpawner::SharePlayerState(UStates_PlayerF::EStates_PlayerF playerState)
{
	if (SpawnedEnemy)
	{
		SpawnedEnemy->SetPlayerState(playerState);
	}
}

int AScene_EnemiesSpawner::GetidZone() { return idZone; }
int AScene_EnemiesSpawner::GetidWave() { return idWave; }


void AScene_EnemiesSpawner::SetId(int currentId) { id = currentId; }
