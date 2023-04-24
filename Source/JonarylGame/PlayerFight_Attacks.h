// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerFight_Actions.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"


#include "PlayerFight_Attacks.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API APlayerFight_Attacks : public APlayerFight_Actions
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void XBtnAction() override;
	virtual void YBtnAction() override;
	virtual void BBtnAction() override;

	void DebugBtnAction() override;


	int currentCombo;
	int currentAttack;
	int AttackOneNumber;

	bool isAttacking;
	bool isStrongAttacking;
	bool canAttack;
	bool canFinalComboAttack;

	bool isCounterStance;
	bool isCounter;
	bool isCounterLeft;
	bool canCounterStance;
	bool canCounter;

	virtual bool GetisAttacking();
	virtual bool GetisStrongAttacking();
	virtual int GetcurrentCombo();
	
	virtual bool GetisCounterStance();
	virtual bool GetisCounter();
	virtual bool GetisCounterLeft();
};
