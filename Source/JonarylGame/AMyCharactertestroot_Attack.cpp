// Fill out your copyright notice in the Description page of Project Settings.


#include "AMyCharactertestroot_Attack.h"


AAMyCharactertestroot_Attack::AAMyCharactertestroot_Attack()
{
	isAttacking = false;
	currentCombo = 0;
	canAttack = true;
	isRightAttack = true;
	isCounterTake = false;
}

void AAMyCharactertestroot_Attack::AttackIsRight()
{
	isRightAttack = true;
}
void AAMyCharactertestroot_Attack::AttackIsLeft()
{
	isRightAttack = false;
}

void AAMyCharactertestroot_Attack::AttackPLayer()
{
	if (canAttack == true)
	{
		isDamaged = false;
		isAttacking = true;
		currentCombo--;
		canAttack = false;
	}
}

void AAMyCharactertestroot_Attack::ModifyDmgBlend(float alpha, float alphaR, float alphaL)
{
	DmgBlendAlpha = alpha;
	DmgBlendR = alphaR;
	DmgBlendL = alphaL;
}
void AAMyCharactertestroot_Attack::DamageTake(int damage, bool isRightDamage)
{
	Super::DamageTake(damage, isRightDamage);
	//isAttacking = false;
	//canAttack = true;

	if (isRightDamage)
		ModifyDmgBlend(0.5f, 1.0f, 0.0f);
	else
		ModifyDmgBlend(0.5f, 0.0f, 1.0f);
}
void AAMyCharactertestroot_Attack::CounterTake()
{
	isCounterTake = true;
	UE_LOG(LogTemp, Error, TEXT("isCounterTake !!!!!!!!!!"));
}


bool AAMyCharactertestroot_Attack::GetisAttacking()
{
	return isAttacking;
}
bool AAMyCharactertestroot_Attack::GetisComboAttacking()
{
	return isComboAttacking;
}
int AAMyCharactertestroot_Attack::GetcurrentCombo()
{
	return currentCombo;
}


float AAMyCharactertestroot_Attack::GetDmgBlendAlpha()
{
	return DmgBlendAlpha;
}
float AAMyCharactertestroot_Attack::GetDmgBlendR()
{
	return DmgBlendR;
}
float AAMyCharactertestroot_Attack::GetDmgBlendL()
{
	return DmgBlendL;
}


void AAMyCharactertestroot_Attack::WaitingForChoice()
{
	return Super::WaitingForChoice();
	isCounterTake = false;
}
void AAMyCharactertestroot_Attack::EndDamage()
{
	EndDamageAnimation();
	WaitingForChoice();
}
void AAMyCharactertestroot_Attack::EndDamageAnimation()
{
	ModifyDmgBlend(0.0f, 0.0f, 0.0f);
}
void AAMyCharactertestroot_Attack::CanAttack()
{
	isAttacking = false;
	isCounterTake = false;
	currentCombo = 0;
	canAttack = true;
	WaitingForChoice();
}


void AAMyCharactertestroot_Attack::ParticleLaunch()
{
	SpawnParticle();
}

void AAMyCharactertestroot_Attack::SpawnParticle()
{
	if (!AttackList.IsEmpty())
	{
		TSubclassOf<AActor> AttackClass = AttackList[0];
		AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(AttackClass, GetActorLocation(), GetActorRotation());

		IIParticle_AttackPlayer* AttackInterface = Cast<IIParticle_AttackPlayer>(AttackInstance);
		AActor* ActorReference = Cast<AActor>(this);
		if (AttackInterface && ActorReference)
		{
			AttackInterface->Execute_SetAttack(AttackInstance, Attack, isRightAttack, GetActorLocation(), ActorReference);

			FVector EnemyLaunchPosition = GetActorLocation();
			//UE_LOG(LogTemp, Warning, TEXT("GetActorLocation GetActorLocation : X=%f, Y=%f, Z=%f"), EnemyLaunchPosition.X, EnemyLaunchPosition.Y, EnemyLaunchPosition.Z);
		}
	}

}
