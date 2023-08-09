// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Stats.h"

// Sets default values
APlayerFight_Stats::APlayerFight_Stats()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerFight_Stats::BeginPlay()
{
	Super::BeginPlay();
	isSuperMode = false;
}

// Called every frame
void APlayerFight_Stats::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerFight_Stats::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

