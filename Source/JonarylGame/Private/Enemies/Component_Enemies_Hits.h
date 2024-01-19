// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Structures/Struct_CharacterStats.h"
#include "Structures/Struct_HitStats.h"
#include "Particle_Enemies_I.h"

#include "Component_Enemies_Hits.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UComponent_Enemies_Hits : public UActorComponent
{
	GENERATED_BODY()

protected:
	////////////////////////// STATS ///////////////////////////
	UPROPERTY(EditAnywhere, Category = "Stats")
		float BaseDamage;
	UPROPERTY(EditAnywhere, Category = "Stats")
		float ArmorDamage;
	UPROPERTY(EditAnywhere, Category = "Stats")
		bool isRightDamage;

	////////////////////////// PARTICLE ///////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		TSubclassOf<AActor> particle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		float timeWhenLaunchParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		float timeWhenEnableDamage;

	IParticle_Enemies_I* AttackInterface;

	////////////////////////// HIT ///////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
		bool isCombo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
		int comboID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
		int attackID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
		int hitID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
		float timeWhenHit;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hit")
		float timeWhenEndHit;

	float timeCurrentAttack;

public:
	void SpawnParticleAttack(FStruct_CharacterStats enemyStats);

	////////////////////////// GET ///////////////////////////
	void GettimeCurrentAttack(float time);
	bool GetisCombo();
	int GetcomboID();
	int GetattackID();
	int GethitID();
	float GettimeWhenHit();
	float GettimeWhenEndHit();
	float GettimeWhenLaunchParticle();
	float GettimeWhenEnableDamage();


		
};
