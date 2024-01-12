// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Player/Component_PlayerF_Hits.h"
#include "Structures/Struct_CharacterStats.h"

#include "Component_PlayerF_Attacks.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UComponent_PlayerF_Attacks : public UActorComponent
{
	GENERATED_BODY()

public:	
	UComponent_PlayerF_Attacks();

	void StartAttack(AActor* enemy, FStruct_CharacterStats playerStatistics);
	void Attack();
	float GettimeCurrentAttack();

	int GetattackID();
	float GettimeAttack();
	float GettimeWhenCanMove();
	float GettimeWhenCanContinueCombo();
	float GettimeWhenStopCombo();
	float GettimeWhenStopAnim();


	void SetEnemyLocked(AActor* enemy);
	void SetPlayerStats(FStruct_CharacterStats playerStatistics);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* enemyLocked;

	////////////////////////// STATS ///////////////////////////
		TArray<UComponent_PlayerF_Hits*> hitList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		int attackID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		float timeAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		float timeWhenCanContinueCombo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		float timeWhenCanMove;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		float timeWhenStopCombo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack")
		float timeWhenStopAnim;

	FStruct_CharacterStats playerStats;

	float timeCurrentAttack;
	int currentCombo;
	int currentHit;
		
};
