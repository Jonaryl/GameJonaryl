// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerFight_Attacks.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerFight_Character.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API APlayerFight_Character : public APlayerFight_Attacks
{
	GENERATED_BODY()

public:

	float GetSpeed() override;
	bool GetisStartJump() override;
	bool GetisIdleJump() override;
	bool GetisDashJump() override;
	bool GetisDash() override;
	bool GetisIdle() override;
	bool GetisSprint() override;
	bool GetisNearGround() override;

	bool GetisAttacking() override;
	bool GetisStrongAttacking() override;
	int GetcurrentCombo() override;
	
	bool GetisCounterStance() override;
	bool GetisCounter() override;
	bool GetisCounterLeft() override;

	void CanAttack();
	void EndCombo();
	void ActionEndCombo();
	void FinalComboAttack();

	void CanCounterStance();
	void EndCounterStance();
	void CanCounterStanceMethod();
	void EndCounterStanceMethod();

	void CanCounter();
	void EndCounter();
};
