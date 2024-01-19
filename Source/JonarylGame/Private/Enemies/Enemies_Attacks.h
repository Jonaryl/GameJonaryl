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

	/////////////////////////// DAMAGE ///////////////////////////
	void DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, float ArmorDamage);
	void ModifyDmgBlend(float alpha, float alphaR, float alphaL);

	bool canBeHit;
	float damagedCooldown;

	float DmgBlendAlpha;
	float DmgBlendR;
	float DmgBlendL;

	/////////////////////////// COUNTER   ///////////////////////////
	bool isCounterPose;
	bool isCounter;
};
