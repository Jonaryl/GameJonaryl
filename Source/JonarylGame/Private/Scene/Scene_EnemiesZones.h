// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/UnrealMathUtility.h"

#include "Player/PlayerF_Character.h"
#include "Scene/Scene_EnemiesSpawner.h"

#include "Scene_EnemiesZones.generated.h"


struct EnemySpwaner
{
	int idSpwaner;
	int idWave;
	AScene_EnemiesSpawner* enemySpawn;
	bool isEnemySpawner;
	bool isEnemyDead;
	
	// Constructeur par defaut
	EnemySpwaner() : idSpwaner(0), idWave(0), enemySpawn(nullptr), isEnemySpawner(false), isEnemyDead(false) {}
};

UCLASS()
class AScene_EnemiesZones : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Zone")
		int idZone;

	///////////////////////// COLLISION /////////////////////////
	UBoxComponent* CollisionAttack;
	bool isActive;

	UFUNCTION()
		void OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnAttackCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	///////////////////////// SPAWNER /////////////////////////
	TArray<EnemySpwaner> allEnemySpanwer;
	TArray<EnemySpwaner> enemySpawned;
	TArray<EnemySpwaner> enemyDead;
	int currentWave;

	TArray<int32> allIds;

	void SpawnEnemies(int wave);

	void CheckAllEnemiesDeath(int wave);
	void CheckIsAllDead(int currentDeadCount);

public:	
	void Begin();

	void CheckIsEnemiesDead(int idEnemy, int wave);

	bool GetisActive();
	int GetidZone();
	void SharePlayerState(UStates_PlayerF::EStates_PlayerF playerState);

};
