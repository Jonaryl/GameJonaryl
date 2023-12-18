// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharactertestroot_Move.h"

#include "NiagaraFunctionLibrary.h" 
#include "Components/BoxComponent.h"
#include "Particle_AttackPlayer.h"
#include "IParticle_AttackPlayer.h"


#include "AMyCharactertestroot_Attack.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API AAMyCharactertestroot_Attack : public AMyCharactertestroot_Move
{
	GENERATED_BODY()
public:
	AAMyCharactertestroot_Attack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
		TArray<TSubclassOf<class AActor>> AttackList;


protected:

	bool canAttack;
	bool isAttacking;
	bool isComboAttacking;
	int currentCombo;
	bool isRightAttack;

	bool isCounterTake;

	float DmgBlendAlpha;
	float DmgBlendR;
	float DmgBlendL;

	void WaitingForChoice() override;
	void AttackPLayer() override;
	void DamageTake(int damage, bool isRightDamage) override;
	virtual void CounterTake();
	virtual void ParticleLaunch();
	virtual void ModifyDmgBlend(float alpha, float alphaR, float alphaL);

	virtual bool GetisAttacking();
	virtual bool GetisComboAttacking();
	virtual int GetcurrentCombo();

	virtual float GetDmgBlendAlpha();
	virtual float GetDmgBlendR();
	virtual float GetDmgBlendL();

	virtual void CanAttack();
	virtual void SpawnParticle();


	virtual void AttackIsRight();
	virtual void AttackIsLeft();

	virtual void EndDamage();
	virtual void EndDamageAnimation();
};