// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Actions.h"

#include "NiagaraFunctionLibrary.h" 
#include "Components/BoxComponent.h"
#include "Particle_AttackPlayer.h"
#include "IParticle_AttackPlayer.h"


#include "Enemy_Attacks.generated.h"


class UNiagaraSystem; 
/**
 * 
 */
UCLASS()
class JONARYLGAME_API AEnemy_Attacks : public AEnemy_Actions
{
	GENERATED_BODY()

public:
	AEnemy_Attacks();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
		TArray<TSubclassOf<class AActor>> AttackList;
	  

protected:

	bool canAttack;
	bool isAttacking;
	bool isComboAttacking;
	int currentCombo;
	bool isRightAttack;

	void WaitingForChoice() override;
	void AttackPLayer() override;
	virtual void ParticleLaunch();

	virtual bool GetisAttacking();
	virtual bool GetisComboAttacking();
	virtual int GetcurrentCombo();

	virtual void CanAttack();
	virtual void SpawnParticle();


	virtual void AttackIsRight();
	virtual void AttackIsLeft();
};
