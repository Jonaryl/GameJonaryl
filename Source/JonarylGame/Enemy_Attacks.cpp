// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Attacks.h"

AEnemy_Attacks::AEnemy_Attacks()
{
	isAttacking = false;
	currentCombo = 0;
	canAttack = true;
	isRightAttack = true;
}

void AEnemy_Attacks::AttackIsRight()
{
	isRightAttack = true;
}
void AEnemy_Attacks::AttackIsLeft()
{
	isRightAttack = false;
}

void AEnemy_Attacks::AttackPLayer()
{
	UE_LOG(LogTemp, Warning, TEXT("canAttack  Attack %d"), canAttack);

	if (canAttack == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack"));
		isAttacking = true;
		currentCombo--;
		canAttack = false;
	}
}




bool AEnemy_Attacks::GetisAttacking()
{
	return isAttacking;
}
bool AEnemy_Attacks::GetisComboAttacking()
{
	return isComboAttacking;
}
int AEnemy_Attacks::GetcurrentCombo()
{
	return currentCombo;
}


void AEnemy_Attacks::WaitingForChoice()
{
	return Super::WaitingForChoice();
}
void AEnemy_Attacks::CanAttack()
{
	isAttacking = false;
	currentCombo = 0;
	canAttack = true;
	WaitingForChoice();
	UE_LOG(LogTemp, Warning, TEXT("canAttack  CanAttack CanAttack vCanAttack %d"), canAttack);

}


void AEnemy_Attacks::ParticleLaunch()
{
	SpawnParticle();
}

void AEnemy_Attacks::SpawnParticle()
{
	//UE_LOG(LogTemp, Warning, TEXT("SpawnParticle"));

	if (!AttackList.IsEmpty())
	{
		TSubclassOf<AActor> AttackClass = AttackList[0];
		AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(AttackClass, GetActorLocation(), GetActorRotation());

		IIParticle_AttackPlayer* AttackInterface = Cast<IIParticle_AttackPlayer>(AttackInstance);
		if (AttackInterface)
		{
			AttackInterface->Execute_SetAttack(AttackInstance, Attack, isRightAttack, GetActorLocation());

			FVector EnemyLaunchPosition = GetActorLocation();
			UE_LOG(LogTemp, Warning, TEXT("GetActorLocation GetActorLocation : X=%f, Y=%f, Z=%f"), EnemyLaunchPosition.X, EnemyLaunchPosition.Y, EnemyLaunchPosition.Z);
		}
	}
	
}