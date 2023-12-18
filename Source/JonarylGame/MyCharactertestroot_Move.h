// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharactertestroot.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

#include "MyCharactertestroot_Move.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API AMyCharactertestroot_Move : public AMyCharactertestroot
{
	GENERATED_BODY()

public:
	AMyCharactertestroot_Move();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	ACharacter* PlayerCharacter;
	float distanceToPlayer;
	float distanceToMovePlace;

	bool canMoveToPlace;
	bool canTrackToPlace;
	bool isPlaceThePlayer;
	bool isWaiting;
	int timeAction;
	int timeWaiting;

	bool isRightAttackHit;
	bool canBeHit;
	bool isDamaged;
	bool canCutAnimByDamage;
	float canBeHitCoolDown;
	int hitCountDamageAnimation;

	float moveFB = 0.0f;
	float moveLR = 0.0f;

	bool isSlow;
	int slowMotionCountDown;
	bool isSlowDownTake;
	virtual bool GetisSlowDownTake();
	virtual void ActivateSlowMode();
	virtual void EndSlowMode();

	void LookAtPlayer();
	void MoveToPlace();
	float GenerateRandomFloat(float Min, float Max);
	int GenerateRandomInt(int Min, int Max);

	FVector DestinationtoMove;
	bool isDestinationPlayer;

	void ActionChoice();
	virtual void WaitingForChoice();

	void ChoiceMoveToPlayer();
	void ChoiceWaitingMove();
	void ChoiceAttackPlayer();

	virtual void AttackPLayer();
	virtual void Combo();

	virtual float GetxMove();
	virtual float GetyMove();

	virtual void DamageTake(int damage, bool isRightDamage);
	virtual void SlowDownTake();
};