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
		isDamaged = false;
		UE_LOG(LogTemp, Warning, TEXT("Attack"));
		isAttacking = true;
		currentCombo--;
		canAttack = false;
	}
}

void AEnemy_Attacks::ModifyDmgBlend(float alpha, float alphaR, float alphaL)
{
	DmgBlendAlpha = alpha;
	DmgBlendR = alphaR;
	DmgBlendL = alphaL;
}
void AEnemy_Attacks::DamageTake(int damage, bool isRightDamage)
{
	Super::DamageTake(damage, isRightDamage);
	UE_LOG(LogTemp, Warning, TEXT("Attack"));
	//isAttacking = false;
	//canAttack = true;

	if (isRightDamage)
		ModifyDmgBlend(0.5f, 1.0f, 0.0f);
	else
		ModifyDmgBlend(0.5f, 0.0f, 1.0f);
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


float AEnemy_Attacks::GetDmgBlendAlpha()
{
	return DmgBlendAlpha;
}
float AEnemy_Attacks::GetDmgBlendR()
{
	return DmgBlendR;
}
float AEnemy_Attacks::GetDmgBlendL()
{
	return DmgBlendL;
}


void AEnemy_Attacks::WaitingForChoice()
{
	return Super::WaitingForChoice();
}
void AEnemy_Attacks::EndDamage()
{
	UE_LOG(LogTemp, Error, TEXT("EndDamage"));
	EndDamageAnimation();
	WaitingForChoice();
}
void AEnemy_Attacks::EndDamageAnimation()
{
	UE_LOG(LogTemp, Error, TEXT("EndDamageAnimation"));
	ModifyDmgBlend(0.0f, 0.0f, 0.0f);
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