// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PlayerFight_Character.h"

#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h" 
#include "Components/BoxComponent.h"
#include "IParticle_AttackPlayer.h"

#include "Particle_AttackPlayer.generated.h"

class UNiagaraSystem;

UCLASS()
class JONARYLGAME_API AParticle_AttackPlayer : public AActor, public IIParticle_AttackPlayer
{
	GENERATED_BODY()
	
public:	
	AParticle_AttackPlayer();

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
		float BaseDamage;
	float enemyAttack;
	UPROPERTY(EditAnywhere, Category = "Stats")
		bool isDamageCut;
	UPROPERTY(EditAnywhere, Category = "Stats")
		int damageCut;

	FVector EnemyLaunchPosition;

	AActor* CurrentEnemy;

	UBoxComponent* CollisionAttack;

	bool isRightDamage;

	void SetAttack_Implementation(int AttackEnemy, bool isRightAttack, FVector emeterPosition, AActor* Enemy) override;
protected:

	void DamagePlayer( APlayerFight_Character* player);
	void LaunchParticle();

	UFUNCTION()
		void OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnAttackCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


};
