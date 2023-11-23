// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerFight_Attacks.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "PlayerFight_Character.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API APlayerFight_Character : public APlayerFight_Attacks
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	UBoxComponent* CollisionDamage;

	float GetSpeed() override;
	float GetvalueTurn();
	bool GetisStartJump() override;
	bool GetisIdleJump() override;
	bool GetisDashJump() override;
	bool GetisDash() override;
	int GetdashNumber() override;
	bool GetisIdle() override;
	bool GetisSprint() override;
	bool GetisNearGround() override;
	bool GetCanMove() override;
	bool GethasLanded() override;
	
	bool AttackSpeB;
	bool AttackSpeX;
	bool AttackSpeY;

	bool GetAttackSpeB();
	bool GetAttackSpeX();
	bool GetAttackSpeY();


	void SetAttackSpeY(bool speB, bool speX, bool speY);

	bool GetisAttacking() override;
	bool GetisStrongAttacking() override;
	int GetcurrentCombo() override;
	int GetAttackOneNumber();
	
	bool GetisCounterStance() override;
	bool GetcanCounterStanceCombo();
	bool GetisCounter() override;
	bool GetisCounterLeft() override;

	bool GetisDamageRight() override;
	bool GetisDamaged() override;
	bool GetisMoving() override;
	int GetdamageAnimNumber();

	int GetcounterNumber();

	void HitCount() override;

	void CanAttack();
	void EndCombo();
	void EndAttack();
	void ActionEndCombo();
	void FinalComboAttack();
	void EndAnimation() override;

	void CanCounterStance();
	void CanCounterStanceMethod();
	void EndCounterStance();
	void EndCounterStanceMethod();

	void ResetEvent();
	void ResetEventMethod();

	void CanCounter();
	void EndCounter();

	void DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, int damageCut, AActor* Enemy) override;

	void SuperModeActivate();
	bool GetisSuperMode();
	void EndSlowEnemy();
};
