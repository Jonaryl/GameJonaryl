// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Attacks.h"
#include "Enemy_Unit.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API AEnemy_Unit : public AEnemy_Attacks
{
	GENERATED_BODY()

public:
	void AttackIsRight() override;
	void AttackIsLeft() override;

	float GetxMove() override;
	float GetyMove() override;

	bool GetisAttacking() override;
	bool GetisComboAttacking() override;
	int GetcurrentCombo() override;

	void CanAttack() override;
	void ParticleLaunch() override;
	void DamageTake(int damage, bool isRightDamage) override;
};
