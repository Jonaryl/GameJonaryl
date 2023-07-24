// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerFight_Actions.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

#include "NiagaraFunctionLibrary.h" 
#include "Components/BoxComponent.h"
#include "IParticle_AttackEnemy.h"

#include "PlayerFight_Attacks.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API APlayerFight_Attacks : public APlayerFight_Actions
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
		TArray<TSubclassOf<AActor>> AttackList;
		//TArray<TSubclassOf<AParticle_AttackEnemy>> AttackList;


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

	int currentHit;

	bool isAttacking;
	bool isStrongAttacking;
	bool canAttack;
	bool canFinalComboAttack;

	bool isRightAttack;

	bool isCounterStance;
	bool isCounter;
	bool isCounterLeft;
	bool canCounterStance;
	bool canCounter;
	bool isDamaged;

	virtual bool GetisAttacking();
	virtual bool GetisStrongAttacking();
	virtual int GetcurrentCombo();
	
	virtual bool GetisCounterStance();
	virtual bool GetisCounter();
	virtual bool GetisCounterLeft();

	virtual bool GetisDamaged();
	virtual bool GetisDamageRight();

	virtual void HitCount();
	virtual void SpawnParticle();
	virtual void DamageTake(int damage, bool isRightDamage);
};
