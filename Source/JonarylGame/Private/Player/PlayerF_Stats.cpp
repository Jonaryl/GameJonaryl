// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerF_Stats.h"

// Sets default values
APlayerF_Stats::APlayerF_Stats()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerF_Stats::BeginPlay()
{
	Super::BeginPlay();
	isSuperMode = false;
}


