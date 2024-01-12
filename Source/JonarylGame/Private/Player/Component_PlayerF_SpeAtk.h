// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GameFramework/WorldSettings.h"

#include "../../Enemy_Unit.h"
#include "Player/Particle_PlayerF_I.h"
#include "Structures/Struct_CharacterStats.h"
#include "Structures/Struct_HitStats.h"

#include "Component_PlayerF_SpeAtk.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UComponent_PlayerF_SpeAtk : public UActorComponent
{
	GENERATED_BODY()

public:	
	UComponent_PlayerF_SpeAtk();

	/////////////////////////// START ///////////////////////////
	virtual void SpecialAttack();

	/////////////////////////// SLOW MOTION ///////////////////////////
	virtual void StartSlowMotion(float slowStrength);
	virtual void EndSlowMotion();
	virtual void AllEnemyEndSlow();

	/////////////////////////// INPUT ///////////////////////////
	virtual void XBtnActionSpe();
	virtual void YBtnActionSpe();
	virtual void BBtnActionSpe();
	virtual void ABtnActionSpe();


	/////////////////////////// TOOL ///////////////////////////
	virtual void GetPlayer(AActor* player);
	virtual void SetEnemyLocked(AActor* enemy);
	virtual void SetPlayerStats(FStruct_CharacterStats playerStatistics);


protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	////////////////////////// PARTICLE ///////////////////////////
	// 0=A 1=B 2=X 3=Y
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		TArray<TSubclassOf<AActor>> particleSpecials;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		TArray<float> timeWhenLaunchParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		TArray<float> timeWhenEnableDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		TArray<float> BaseDamages;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		TArray<float> ArmorDamages;
	
	IParticle_PlayerF_I* AttackInterface;
	float timeCurrentSpecialAtk;
	int indexParticle;

	bool isSpecialAttacking;

	FStruct_CharacterStats playerStats;
	AActor* enemyLocked;

	virtual void LaunchParticle(FStruct_CharacterStats playerStatistics, AActor* enemy, int index);


		
};
