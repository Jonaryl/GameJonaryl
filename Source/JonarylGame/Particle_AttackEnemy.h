// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Enemy_Unit.h"

#include "NiagaraFunctionLibrary.h" 
#include "Components/BoxComponent.h"
#include "IParticle_AttackEnemy.h"

#include "Particle_AttackEnemy.generated.h"

class UNiagaraSystem;

UCLASS()
class JONARYLGAME_API AParticle_AttackEnemy : public AActor, public IIParticle_AttackEnemy
{
	GENERATED_BODY()
	
public:	
	AParticle_AttackEnemy();

	UPROPERTY(EditAnywhere, meta = (MetaAttribute = "ParticlePosition", DisplayName = "Particle Position"))
		FVector ParticlePosition;
	UPROPERTY(EditAnywhere, meta = (MetaAttribute = "ParticleRotation", DisplayName = "Particle Rotation"))
		FRotator ParticleRotation;
	UPROPERTY(EditAnywhere, meta = (MetaAttribute = "ParticleDistance", DisplayName = "Particle Distance"))
		float ParticleDistance;

	UPROPERTY(EditAnywhere, meta = (MetaAttribute = "CollisionSize", DisplayName = "Collision Size"))
		FVector CollisionSize;

	UPROPERTY(EditAnywhere, meta = (MetaAttribute = "Particle", DisplayName = "Particule"))
		UNiagaraSystem* Particle;

	UPROPERTY(EditAnywhere, Category = "Stats")
		bool isSpeSlow;	
	UPROPERTY(EditAnywhere, Category = "Stats")
		bool isCounter;	

	UPROPERTY(EditAnywhere, Category = "Stats")
		float BaseDamage;
	float playerAttack;

	bool isRightDamage;
	UBoxComponent* CollisionAttack;

protected:

	void DamageEnemy(AEnemy_Unit* enemy);
	void LaunchParticle();

	UFUNCTION()
		void OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnAttackCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void BeginPlay() override;

	void SetAttack_Implementation(int AttackPlayer, bool isRightAttack) override;
	void IsCountered_Implementation(AActor* EnemyCountered) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
