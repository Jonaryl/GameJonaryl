// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Attacks.h"

#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

#include "Enemy_Unit.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API AEnemy_Unit : public AEnemy_Attacks
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	UBoxComponent* CollisionDamage;

	void AttackIsRight() override;
	void AttackIsLeft() override;

	float GetxMove() override;
	float GetyMove() override;

	bool GetisAttacking() override;
	bool GetisComboAttacking() override;
	int GetcurrentCombo() override;

	void ModifyDmgBlend(float alpha, float alphaR, float alphaL) override;
	float GetDmgBlendAlpha() override;
	float GetDmgBlendR() override;
	float GetDmgBlendL() override;

	bool GetisDamaged();
	bool GetisDamagedRight();
	int GethitCountDamageAnimation();


	void CanAttack() override;
	void ParticleLaunch() override;
	void DamageTake(int damage, bool isRightDamage) override;

	void EndAnimation();

	void EndDamage() override;
	void EndDamageAnimation() override;

	void ActivateSlowMode() override;
	void EndSlowMode() override;
	void SlowDownTake() override;
	bool GetisSlowDownTake() override;

};
