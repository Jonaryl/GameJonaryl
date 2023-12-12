// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Animation.h"

UEnemy_Animation::UEnemy_Animation()
{

}

void UEnemy_Animation::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	enemyClass = Cast<AEnemy_Unit>(TryGetPawnOwner());
}

void UEnemy_Animation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (enemyClass)
	{
		UpdateAnimProperties();
	}
	else
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy_Unit::StaticClass(), OutActors);

		for (AActor* Actor : OutActors)
		{
			enemyClass = Cast<AEnemy_Unit>(Actor);
			if (enemyClass)
			{
				UpdateAnimProperties();
				break;
			}
		}
	}
}

void UEnemy_Animation::UpdateAnimProperties()
{
	xMove = enemyClass->GetxMove();
	yMove = enemyClass->GetyMove();
	isAttacking = enemyClass->GetisAttacking();
	currentCombo = enemyClass->GetcurrentCombo();
	isDamaged = enemyClass->GetisDamaged();
	isRightAttackHit = enemyClass->GetisDamagedRight();
	hitCountDamageAnimation = enemyClass->GethitCountDamageAnimation();

	DmgBlendAlpha = enemyClass->GetDmgBlendAlpha();
	DmgBlendR = enemyClass->GetDmgBlendR();
	DmgBlendL = enemyClass->GetDmgBlendL();

	isSlowDownTake = enemyClass->GetisSlowDownTake();
	isCounterTake = enemyClass->GetisCounterTake();
	ArmorValue = enemyClass->GetArmorValue();
	/*if (ArmorValue < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ANIMATION ENEMY  isDamaged isDamaged = %s"), isDamaged ? TEXT("True") : TEXT("False"));
		UE_LOG(LogTemp, Error, TEXT("ANIMATION ENEMY  ArmorValue ArmorValue %f"), ArmorValue );
	}*/
	//UE_LOG(LogTemp, Warning, TEXT(" UpdateAnimProperties isCounterStance = %s"), isCounterStance ? TEXT("True") : TEXT("False"));
}

void UEnemy_Animation::CanAttackEvent_Implementation()
{
	enemyClass->CanAttack();
}
void UEnemy_Animation::LaunchParticleEvent_Implementation() 
{
	enemyClass->ParticleLaunch(); 
}

void UEnemy_Animation::AttackIsRight_Implementation()
{
	enemyClass->AttackIsRight();
}
void UEnemy_Animation::AttackIsLeft_Implementation()
{
	enemyClass->AttackIsLeft();
}
void UEnemy_Animation::EndAnimationEvent_Implementation()
{
	enemyClass->EndAnimation();
}

void UEnemy_Animation::EndDamage_Implementation()
{
	enemyClass->EndDamage();
}
void UEnemy_Animation::EndDamageAnimation_Implementation()
{
	enemyClass->EndDamageAnimation();
}

void UEnemy_Animation::ActivateSlowMode_Implementation()
{
	enemyClass->ActivateSlowMode();
}

void UEnemy_Animation::StopAttackTurn_Implementation()
{
	enemyClass->StopAttackTurn();
}

void UEnemy_Animation::EndArmorDamage_Implementation()
{
	enemyClass->EndArmorDamage();
}