// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Enemies/Enemies_Unit.h"

#include "Scene_EnemiesSpawner.generated.h"

UCLASS()
class AScene_EnemiesSpawner : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "Zone")
		int idZone;	
	UPROPERTY(EditAnywhere, Category = "Zone")
		int idWave;

	int id;

	UPROPERTY(EditAnywhere, Category = "Spawn")
		TSubclassOf<class AEnemies_Unit> EnemyClass;

	AEnemies_Unit* SpawnedEnemy;


public:	
	void SharePlayerState(UStates_PlayerF::EStates_PlayerF playerState);
	void SpawnEnemy();

	int GetidZone();
	int GetidWave();

	void SetId(int currentId);
};
