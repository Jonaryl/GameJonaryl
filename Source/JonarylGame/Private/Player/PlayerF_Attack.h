// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerF_Action.h"

#include "Components/PostProcessComponent.h"

#include "Player/Component_PlayerF_Attacks.h"
#include "Player/Component_PlayerF_SpeAtk.h"
#include "Player/Particle_PlayerF_I.h"
#include "Structures/Struct_CharacterStats.h"

#include "PlayerF_Attack.generated.h"

/**
 * 
 */
UCLASS()
class APlayerF_Attack : public APlayerF_Action
{
	GENERATED_BODY()
	
protected:
	/////////////////////////// BASE METHOD ///////////////////////////
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void NeutralAction() override;
	virtual void StopMovingAnim() override;
	virtual void EndPartialAction() override;

	/////////////////////////// INPUT ///////////////////////////
	virtual void ABtnAction() override;
	virtual void BBtnAction() override;
	virtual void XBtnAction() override;
	virtual void YBtnAction() override;
	/////////////////////////// ATTACK ///////////////////////////
	///// ATTACK VARIABLE //////
	TArray<UComponent_PlayerF_Attacks*> attackList;

	bool canAttack;
	bool onCombo;
	float timeCurrentAttack;

	int currentHitCombo;
	bool isAttacking;
	////////////// ATTACK ANIMATION VARIABLE /////////////
	int AttackOneNumber;

	///// ATTACK METHOD //////
	virtual void EndAttack();

	/////////////////////////// SPECIAL ///////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		TSubclassOf<UComponent_PlayerF_SpeAtk> SpecialAttackSubClass;
	UComponent_PlayerF_SpeAtk* SpecialAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		TSubclassOf<AActor> CanAtkSpeFlashParticle;

	bool canAttackSpe;

	////////////// SPECIAL ANIMATION VARIABLE /////////////
	bool isSuperMode;

	bool isSpeActionA;
	bool isSpeActionB;
	bool isSpeActionX;
	bool isSpeActionY;

public:
	void SuperModeActivate();
	virtual void PostProcessSlowActivate(bool isActivate);
	void LaunchAtkSpeFlashParticle();
	 
	/////////////////////////// DAMAGE ///////////////////////////
	virtual void DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, AActor* Enemy, float ArmorDamage, int damageId) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
		float timeCanMoveDamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
		float timeEndDamage;
	float damagedCooldown;
	float regenArmorCooldown;
	int lastDamageID;

	int damageAnimNumber;
	bool isDamageRight;

	/////////////////////////// COUNTER ///////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		TSubclassOf<AActor> CounterParticleL;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		TSubclassOf<AActor> CounterParticleR;

	UPostProcessComponent* PostProcessSlow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
		float timeStartCounterPose;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
		float timeStopCounterPose;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
		float timeCanActionCounterPose;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
		float timeStopAnimCounterPose;

	float timeCounterPose;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
	//	float timeStartCounter;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
	//	float timeStopCounter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
		float timeCanAttackSpe;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
		float timeStopCanAttackSpe;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
		float timeCanActionCounter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
		float timeStopAnimCounter;

	float timeCounter;

	bool canCounterPose;
	bool canCounter;

	////////////// COUNTER ANIMATION VARIABLE /////////////
	bool isCounterPose;
	bool isCounter;
	bool isRightCounter;

	int counterPoseNumber;
	int counterNumber;


	void EndCounterPose();
	void EndCounter();
	
	void SpawnParticleCounter(bool isRightDamage, AActor* Enemy);

	////////////// DEBUG /////////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
		int whishAttackToDebug;
	virtual void DebugBtnAction() override;

};
