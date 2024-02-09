// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/Enemies_Classe.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

#include "States_EnemiesActions.h"
#include "States_EnemiesBehaviors.h"
#include "Player/States_PlayerF.h"

#include "Enemies_Move.generated.h"

/**
 * 
 */
UCLASS()
class AEnemies_Move : public AEnemies_Classe
{
	GENERATED_BODY()

protected:
	/////////////////////////// BASE METHOD ///////////////////////////
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;



	/////////////////////////// BASE Variable ///////////////////////////
	ACharacter* EnemyPawn;
	UBoxComponent* CollisionEnemy;

	/////////////////////////// MOVING ///////////////////////////
	///// MOVING VARIABLE //////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float maxRunSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float maxSprintSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float maxWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float runRotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float distanceToMovePlace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float distanceToStopToPlayer;
	
	////////////// MOVING ANIMATION VARIABLE /////////////
	FVector xyMovingValue;
	bool isMoving;
	bool isIdle;

	////////////// MOVING ANIMATION METHOD /////////////
	virtual void GetxyMovingValue(FVector previousPosition, FVector nextPosition);


	///// MOVING METHOD //////
	virtual void Moving(FVector destinationToGo);
	virtual void Turning(FVector destinationToLookAt, float speed = 1.0f);

	virtual FVector GetPlacePosition();
	float GetPlaceDistance(FVector place);
	/////////////////////////// DEAD ///////////////////////////
	int id;
	int idZone;
	int idWave;
	bool isEnemyDead;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dead")
		float deathAnimationCooldown;
	/////////////////////////// STATES ///////////////////////////
	////ACTIONS/////
	UStates_EnemiesActions::EStates_EnemiesActions CurrentActionState = UStates_EnemiesActions::EStates_EnemiesActions::Idle;

	virtual void SetActionState(UStates_EnemiesActions::EStates_EnemiesActions NewState, float Time);
	virtual void ChangeActionState(UStates_EnemiesActions::EStates_EnemiesActions NewState);

	////BEHAVIOURS/////
	UStates_EnemiesBehaviors::EStates_EnemiesBehaviors CurrentBehaviorsState = UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::WaitingNextAction;

	virtual void SetBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors NewState, float Time);
	virtual void ChangeBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors NewState);

	/////////////////////////// PLAYER INFO ///////////////////////////
	///// PLAYER INFO VARIABLE //////

	ACharacter* PlayerCharacter;
	UStates_PlayerF::EStates_PlayerF CurrentPlayerState = UStates_PlayerF::EStates_PlayerF::Idle;


	///// PLAYER INFO METHOD //////
	virtual FVector GetPlayerPosition();
	virtual float GetPlayerDistance();

	/////////////////////////// DELEGATE ///////////////////////////
	virtual void ReactionToPlayer();
	virtual void StopAllActions();

	virtual void NewAction();

	/////////////////////////// TOOLS  ///////////////////////////
	float GenerateRandomFloat(float Min, float Max);
	int GenerateRandomInt(int Min, int Max);

public:
	void SetIds(int currentId, int currentIdZone, int currentIdWave);


	void SetPlayerState(UStates_PlayerF::EStates_PlayerF playerStates);
};
