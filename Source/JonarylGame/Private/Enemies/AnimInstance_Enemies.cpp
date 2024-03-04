// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/AnimInstance_Enemies.h"


void UAnimInstance_Enemies::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	enemyClass = Cast<AEnemies_Unit>(TryGetPawnOwner());
}
void UAnimInstance_Enemies::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (enemyClass)
	{
		UpdateAnimProperties();
	}
	else
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemies_Unit::StaticClass(), OutActors);

		for (AActor* Actor : OutActors)
		{
			enemyClass = Cast<AEnemies_Unit>(Actor);
			if (enemyClass)
			{
				UpdateAnimProperties();
				break;
			}
		}
	}
}

//ANIMATION UPDATE
void UAnimInstance_Enemies::UpdateAnimProperties()
{
	//MOVE
	isIdle = enemyClass->GetisIdle();
	isMoving = enemyClass->GetisMoving();
	isRuning = enemyClass->GetisRuning();
	xValueMove = enemyClass->GetxMoving();
	yValueMove = enemyClass->GetyMoving();

	//ATTACK
	isAttackStarted = enemyClass->GetisAttackStarted();
	currentHitCombo = enemyClass->GetcurrentHitCombo();
	isAttackCombo = enemyClass->GetisAttackCombo();

	//DASH
	isDashBack = enemyClass->GetisDashBack();
	isDashLeft = enemyClass->GetisDashLeft();
	isDashRight = enemyClass->GetisDashRight();
	dashNumber = enemyClass->GetdashNumber();

	//DAMAGE
	isDamaged = enemyClass->GetisDamaged();
	isRightAttackHit = enemyClass->GetisRightAttackHit();

	hitCountDamageAnimation = enemyClass->GethitCountDamageAnimation();

	DmgBlendAlpha = enemyClass->GetDmgBlendAlpha();
	DmgBlendR = enemyClass->GetDmgBlendR();
	DmgBlendL = enemyClass->GetDmgBlendL();

	isCounterTake = enemyClass->GetisCounterTake();
	isSlowDownTake = enemyClass->GetisSlowDownTake();

	isEnemyDead = enemyClass->GetisEnemyDead();

	//COUNTER
	isCounterPose = enemyClass->GetisCounterPose();
	isCounter = enemyClass->GetisCounter();
}




//EVENTS
void UAnimInstance_Enemies::EventAnim_Implementation()
{
	enemyClass->EventAnim();
}
void UAnimInstance_Enemies::LaunchParticle_Implementation()
{
	enemyClass->LaunchParticle();
}
void UAnimInstance_Enemies::EnableDamage_Implementation()
{
	enemyClass->EnableDamage();
}
void UAnimInstance_Enemies::AdvertAttack_Implementation()
{
	enemyClass->AdvertAttack();
}