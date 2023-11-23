// Fill out your copyright notice in the Description page of Project Settings.


#include "Scene_Spawner.h"

// Sets default values
AScene_Spawner::AScene_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScene_Spawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemy();
}

// Called every frame
void AScene_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScene_Spawner::SpawnEnemy()
{
	if (EnemyClass && canSpawn)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		//SpawnParams.Instigator = Instigator;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.OverrideLevel = GetLevel();
		SpawnParams.ObjectFlags |= RF_Transient;	// We never want to save AI controllers into a map

		FVector SpawnLocation = GetActorLocation() + FMath::RandPointInBox(GetComponentsBoundingBox());
		FRotator SpawnRotation;

		UE_LOG(LogTemp, Warning, TEXT("SpawnLocation: %s"), *SpawnLocation.ToString());


		// Spawn the enemy
		AEnemy_Unit* SpawnedEnemy = GetWorld()->SpawnActor<AEnemy_Unit>(EnemyClass, SpawnLocation, SpawnRotation, SpawnParams);


		UE_LOG(LogTemp, Warning, TEXT(" spawn "));
	}
}

