// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/PrimitiveComponent.h"

#include "PlayerFight_Lock.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JONARYLGAME_API UPlayerFight_Lock : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFight_Lock();

	AActor* GetLastTarget();
	void Test();
	void GetPlayerPosRot(FVector playerPos, FRotator playerRot, AActor* player, FVector frontVector);

	void Update();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<AActor> ActorList;

	AActor* EnemyTarget;
	AActor* PlayerFrom;
	FVector playerPosition;
	FRotator playerRotation;
	FVector playerFrontVector;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
