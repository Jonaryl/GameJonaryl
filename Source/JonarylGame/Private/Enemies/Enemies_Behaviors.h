// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/Enemies_Attacks.h"

#include "Engine/Engine.h"
#include "Math/RandomStream.h"
#include "Math/UnrealMathUtility.h"

#include "Enemies_Behaviors.generated.h"

struct BehaviorValues
{
	int timeBehavior;
	bool isActionEnded;
};

/**
 * 
 */
UCLASS()
class AEnemies_Behaviors : public AEnemies_Attacks
{
	GENERATED_BODY()
	
protected:
	/////////////////////////// BASE METHOD ///////////////////////////
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;



	/////////////////////////// BASE BEHAVIOURS ///////////////////////////
	BehaviorValues behaviorValues;
	float waitingTime;
	float distanceTurnPlayer;
	float directiontoTurn;

	float maxTimeAction;
	FVector PlaceToMoveLocation;

	void WaitingTimeBetwenAction();
	void ChooseNextAction();

	void MoveToPlayer(float distanceMaxMultiple, UStates_EnemiesActions::EStates_EnemiesActions state);
	void MoveToPlace(UStates_EnemiesActions::EStates_EnemiesActions state);

	void TurningAroundPlayer(float distanceMaxMultiple, UStates_EnemiesActions::EStates_EnemiesActions state);

	void AttackPlayer();
	virtual void NextAttack() override;
	virtual void EndAttack() override;

	/////////////////////////// REACTION BEHAVIOURS ///////////////////////////
	int randomIntChoice;

	virtual void ReactionToPlayer() override;


	void DodgeAttack();
	void CounterAttack();

	/////////////////////////// DELEGATE ///////////////////////////
	virtual void StopAllActions()  override;
};
