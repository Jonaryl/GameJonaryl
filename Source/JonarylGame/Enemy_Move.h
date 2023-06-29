// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Classes.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"



#include "Enemy_Move.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API AEnemy_Move : public AEnemy_Classes
{
	GENERATED_BODY()

public:
	AEnemy_Move();
	virtual void Tick(float DeltaTime) override;

protected:
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
	float canBeHitCoolDown;

	float moveFB = 0.0f;
	float moveLR = 0.0f;

	void LookAtPlayer();
	void MoveToPlace();
	float GenerateRandomFloat(float Min, float Max);
	int GenerateRandomInt(int Min, int Max);

	FVector DestinationtoMove;

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
};
