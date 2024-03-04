// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component_PlayerF_Lock.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UComponent_PlayerF_Lock : public UActorComponent
{
	GENERATED_BODY()

public:	
	void Update(FVector playerPosition, FVector playerNextPosition);

	AActor* GetLastTarget();
	void EnemyDead();

protected:
	AActor* EnemyTarget;
		
};
