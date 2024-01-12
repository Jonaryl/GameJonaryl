// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "NiagaraFunctionLibrary.h" 
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Player/Particle_PlayerF_I.h"
#include "Player/PlayerF_Character.h"
#include "Structures/Struct_CharacterStats.h"
#include "Structures/Struct_HitStats.h"
#include "../../Enemy_Unit.h"

#include "Particle_PlayerF.generated.h"

class UNiagaraSystem;
UCLASS()
class AParticle_PlayerF : public AActor, public IParticle_PlayerF_I
{
	GENERATED_BODY()
	
public:	
	AParticle_PlayerF();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	////////////////////////// OBJECT ///////////////////////////
	UBoxComponent* CollisionAttack;
	APlayerF_Character* player;
	AEnemy_Unit* currentEnemyLocked;


	////////////////////////// PARTICLE ///////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		FVector ParticlePosition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		FRotator ParticleRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		UNiagaraSystem* particle;

	void LaunchParticle();


	////////////////////////// COLLISION ///////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		FVector ColisionPosition;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		FRotator ColisionRotation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particle")
		FVector CollisionSize;

	UFUNCTION()
		void OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnAttackCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	void DamageEnemy(AEnemy_Unit* enemy);

	////////////////////////// STATS ///////////////////////////
	UPROPERTY(EditAnywhere, Category = "Stats")
		bool isSpeSlow;
	UPROPERTY(EditAnywhere, Category = "Stats")
		bool isCounter;

	UPROPERTY(EditAnywhere, Category = "Stats")
		bool isSpeTimeDestroy;
	UPROPERTY(EditAnywhere, Category = "Stats")
		float speTimeDestroy;

	FStruct_CharacterStats currentPlayerStats;
	FStruct_HitStats currentHitStats;

	void SetAttack_Implementation(FStruct_CharacterStats playerStats, FStruct_HitStats hitStats, AActor* currentPlayer, AActor* enemyLocked) override;
	void IsCountered_Implementation(AActor* EnemyCountered) override;
};
