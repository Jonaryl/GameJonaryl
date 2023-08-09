// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy_Unit.h"
#include "Scene_Spawner.generated.h"

UCLASS()
class JONARYLGAME_API AScene_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScene_Spawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Spawn")
		TSubclassOf<class AEnemy_Unit> EnemyClass;
	UPROPERTY(EditAnywhere, Category = "Spawn")
		bool canSpawn;

	void SpawnEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
