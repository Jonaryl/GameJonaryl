// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Player/States_PlayerF.h"
#include "Scene/Scene_EnemiesZones.h"
#include "Player/PlayerF_Character.h"

#include "Scene_EnemiesManager.generated.h"

UCLASS()
class AScene_EnemiesManager : public AActor
{
	GENERATED_BODY()
	
protected:
	/////////////////////////// BASE METHOD ///////////////////////////
	AScene_EnemiesManager();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	/////////////////////////// ENEMY INFOS ///////////////////////////
	TArray<AScene_EnemiesZones*> allEnemiesZones;
	
	/////////////////////////// PLAYER INFOS ///////////////////////////
	APlayerF_Character* PlayerCharacter;
	UStates_PlayerF::EStates_PlayerF CurrentPlayerState = UStates_PlayerF::EStates_PlayerF::Idle;
public:
	///////////////////////// FOR PLAYER /////////////////////////
	void SharePlayerState(UStates_PlayerF::EStates_PlayerF playerState);

	///////////////////////// FOR ENEMIES /////////////////////////
	void EnemyIsDead(int id, int idZone, int idWave);
};
