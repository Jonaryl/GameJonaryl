// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NiagaraFunctionLibrary.h" 
#include "Components/BoxComponent.h"
#include "PlayerFight_Character.h"


#include "Particle_Ennemy.generated.h"

class UNiagaraSystem;

UCLASS()
class JONARYLGAME_API AParticle_Ennemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParticle_Ennemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
