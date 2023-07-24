// Fill out your copyright notice in the Description page of Project Settings.


#include "Particle_Ennemy.h"

// Sets default values
AParticle_Ennemy::AParticle_Ennemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParticle_Ennemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParticle_Ennemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

