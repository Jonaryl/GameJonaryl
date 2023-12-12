// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Classes.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Enemy_Move.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API AEnemy_Move : public AEnemy_Classes
{
	GENERATED_BODY()

public:
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

	bool isAttacking;
	bool canTurnToPlayer;

	bool isRightAttackHit;
	bool canBeHit;
	bool isDamaged;
	bool canCutAnimByDamage;
	float canBeHitCoolDown;
	int hitCountDamageAnimation;
	int damageCount;

	int currentHealth;
	float currentArmorValue;
	float armorRegenCoolDown;

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

	virtual void DamageTake(int damage, bool isRightDamage, float ArmorDamage);
	virtual void SlowDownTake();
	virtual void EndArmorDamage();

	int actionCooldown;
	virtual void StopAction();
};
