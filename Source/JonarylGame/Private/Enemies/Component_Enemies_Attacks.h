// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Component_Enemies_Hits.h"
#include "Structures/Struct_CharacterStats.h"

#include "Component_Enemies_Attacks.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UComponent_Enemies_Attacks : public UActorComponent
{
	GENERATED_BODY()


protected:
	UComponent_Enemies_Attacks();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	////////////////////////// STATS ///////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		bool isCombo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		int comboID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		int attackID;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		float timeAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		float timeNextAttackCombo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		float timeStopAnim;

	FStruct_CharacterStats enemyStats;

	////////////////////////// ATTACK AND HITS ///////////////////////////
	TArray<UComponent_Enemies_Hits*> hitList;
	int currentCombo;
	int currentHit;

	UComponent_Enemies_Hits* hitInstance;

public:
	void StartAttack(FStruct_CharacterStats enemyStatistics);
	void Attack(float timeCurrentAttack);

	void LaunchParticle();
	void EnableDamage();

	////////////////////////// STATS ///////////////////////////
	bool GetisCombo();
	int GetcomboID();
	int GetattackID();
	float GettimeAttack();
	float GettimeNextAttackCombo();
	float GettimeStopAnim();
};
