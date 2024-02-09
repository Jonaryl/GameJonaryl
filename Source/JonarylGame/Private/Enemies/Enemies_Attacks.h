// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/Enemies_Actions.h"

#include "Enemies/Component_Enemies_Attacks.h"

#include "Enemies_Attacks.generated.h"

/**
 * 
 */
UCLASS()
class AEnemies_Attacks : public AEnemies_Actions
{
	GENERATED_BODY()
	
protected:
	/////////////////////////// BASE METHOD ///////////////////////////
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	/////////////////////////// ATTACK ///////////////////////////
	///// ATTACK VARIABLE //////
	TArray<UComponent_Enemies_Attacks*> attackList;
	
	TArray<UComponent_Enemies_Attacks*> comboA;
	TArray<UComponent_Enemies_Attacks*> comboB;
	TArray<UComponent_Enemies_Attacks*> comboC;
	TArray<UComponent_Enemies_Attacks*> comboD;
	TArray<UComponent_Enemies_Attacks*> comboE;

	TArray<UComponent_Enemies_Attacks*> currentAttacklist;
	UComponent_Enemies_Attacks* attackInstance;
	int numberOfCombo;

	bool isAttackStarted;
	bool isAttackCombo;

	int currentHitCombo;
	int choiceCombo;
	int numberOfHit;

	///// ATTACK METHOD //////
	void StartAttack(bool isCombo);
	void Attack(int timeCurrentAttack);
	virtual void EndAttack();
	virtual void NextAttack();

	virtual void LaunchParticle();
	virtual void EnableDamage();

	/////////////////////////// DAMAGE ///////////////////////////
public:
	void DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, float ArmorDamage, int damageId);
	virtual void SlowDownTake();
	virtual bool GetisSlowDownTake();
	virtual void EndSlowMode();

protected:
	void ModifyDmgBlend(float alpha, float alphaR, float alphaL);
	virtual void CounterTake();

	virtual void ActivateSlowMode();

	bool isSlow;
	int slowMotionCountDown;
	bool isSlowDownTake;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
		float maxDamagedCooldown;
	float currentDamagedCooldown;
	float regenArmorCooldown;

	int lastDamageID;
	float HitCooldown;
	int hitCountDamageAnimation;

	bool isCounterTake;

	bool isDamaged;
	bool isRightAttackHit;

	float DmgBlendAlpha;
	float DmgBlendR;
	float DmgBlendL;

	/////////////////////////// COUNTER   ///////////////////////////
	bool isCounterPose;
	bool isCounter;

	bool canCounter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CounterPose") 
		int timeStopCounterPose; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CounterPose")
		int timeStopAnimCounterPose;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
		int timeStopCounter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Counter")
		int timeEndCounter;

	virtual bool CounterPose(int actionCounterPoseTurn);
	virtual bool Counter(int actionCounterTurn);
	/////////////////////////// DEBUG   ///////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
		int whishAttackToDebug;


};
