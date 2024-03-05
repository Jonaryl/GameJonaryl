// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/Enemies_Attacks.h"

#include "Engine/Engine.h"
#include "Math/RandomStream.h"
#include "Math/UnrealMathUtility.h"

#include "States_EnemiesActions.h"

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


	void SendMessageManager();
	/////////////////////////// BASE BEHAVIOURS ///////////////////////////
	BehaviorValues behaviorValues;
	float waitingTime;
	float distanceTurnPlayer;
	float directiontoTurn;

	float maxTimeAction;
	FVector PlaceToMoveLocation;

	void WaitingTimeBetwenAction();
	void ChooseNextAction();

	void MoveToPlayer(float distanceMaxMultiple, EStates_EnemiesActions state);
	void MoveToPlace(EStates_EnemiesActions state);

	void TurningAroundPlayer(float distanceMaxMultiple, EStates_EnemiesActions state);

	void AttackPlayer();
	virtual void NextAttack() override;
	virtual void EndAttack() override;

	/////////////////////////// REACTION BEHAVIOURS ///////////////////////////
	int randomIntChoice;

	virtual void ReactionToPlayer() override;


	void ReactionToAttacks();
	void DodgeAttack();
	void CounterAttack();

	///////////////////////////  BEHAVIOURS probability ///////////////////////////
	TArray<FString> ListBehaviors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		bool canChasing;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		int probabilityChasing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		bool canAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		int probabilityAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		bool canTurningAround;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		int probabilityTurningAround;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		bool canEvaluate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		int probabilityEvaluate;


	/////// REACTIONS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		TArray<TEnumAsByte<EStates_EnemiesActions>> StateEnemyWhenCantReact;

	bool canReact;

	TArray<FString> ListReactionsBehaviors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		float timeLagReactionMin;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		float timeLagReactionMax;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		bool canDodgeProba;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		int probabilityDodge;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		bool canCounterProba;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Probability")
		int probabilityCounter;

	/////////////////////////// DELEGATE ///////////////////////////
	virtual void StopAllActions()  override;
	virtual void NewAction()  override;
};
