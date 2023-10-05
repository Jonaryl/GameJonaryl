// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Attacks.h"


void APlayerFight_Attacks::BeginPlay()
{
	Super::BeginPlay();
	currentCombo = 0;
	currentHit = 0;
	currentAttack = 0;
	isAttacking = false;
	isStrongAttacking = false;
	isMoveInput = false;
	canFinalComboAttack = false;
	canAttack = true;

	isCounterStance = false;
	isCounter = false;
	isCounterLeft = false;
	canCounterStance = true;
	canCounter = false;

	dashNumber = 0;

	isRightAttack = true;
	isDamaged = false;
	canCounterAttack = false;
	canBeHit = true;

	currentDamageCut = cutDamageStamina;

	if (SpecialAttack)
	{
		SpecialAttacknstance = NewObject<UPlayerFight_SpecialAttack>(this, SpecialAttack);
	}
}

void APlayerFight_Attacks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentDamageCut <= cutDamageStamina)
	{
		currentDamageCut++;
	}


	if (currentCounterGauge > 0)
	{
		currentCounterGauge = currentCounterGauge - 0.001f;
		//UE_LOG(LogTemp, Warning, TEXT(" Tick currentCounterGauge = %f"), currentCounterGauge);
	}
	if (slowMotionCooldown > 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("DamageTake slowMotionCooldown %d"), slowMotionCooldown);
		slowMotionCooldown--;
		canCounterAttack = true;
	}
	else if (slowMotionCooldown > 0 && slowMotionCooldown <= 2)
	{
		canCounterAttack = true;
		slowMotionCooldown--;
	}
	else if (slowMotionCooldown <= 0 && canCounterAttack == true)
	{
		canCounterAttack = false;
		UE_LOG(LogTemp, Error, TEXT("STOP DamageTake canCounterAttack canCounterAttack %d"), slowMotionCooldown);
		if(SpecialAttacknstance)
			SpecialAttacknstance->EndSlowMotion();
	}

	if(canBeHit == false)
	{
		canBeHitCoolDown--;
		if (canBeHitCoolDown < 0)
		{
			canBeHit = true;
			isDamaged = false;
		}
	}


	if (CurrentState == APlayerFight_States::EPlayerFight_State::Attack && isAttacking)
	{
		if (enemyTargetLock != nullptr)
		{
			FRotator lookAtRotationForTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), enemyTargetLock->GetActorLocation());
			FQuat InterpolatedRotationForTarget = FQuat::Slerp(GetActorRotation().Quaternion(), lookAtRotationForTarget.Quaternion(), GetWorld()->DeltaTimeSeconds * runRotationSpeed);
			RotatingFormDirection(InterpolatedRotationForTarget);
		}
		else if (timerWhenCanTurnAttacking > 0)
		{
			Rotating();
			timerWhenCanTurnAttacking--;
		}
		//USkeletalMeshComponent* MeshComponentAttack = GetMesh();
		//UAnimInstance* AnimInstance = MeshComponentAttack->GetAnimInstance();
		//if (AnimInstance == nullptr)
		//{
		//	return;
		//}

		//FVector CurrentVelocityAttack = MeshComponentAttack->GetPhysicsLinearVelocity();
		//FVector NewLocationAttack = GetActorLocation() + CurrentVelocityAttack * GetWorld()->GetDeltaSeconds();
		//SetActorLocation(NewLocationAttack);

		//UE_LOG(LogTemp, Warning, TEXT("attack move"));
		//FTransform RootMotionTransform = GetRootMotionDeltaTransform();

		//// Applique la transformation au personnage
		//if (!RootMotionTransform.IsIdentity())
		//{
		//	FVector NewLocation = GetActorLocation() + RootMotionTransform.GetTranslation();
		//	SetActorLocation(NewLocation);

		//	FRotator NewRotation = RootMotionTransform.GetRotation().Rotator() * GetActorRotation();
		//	SetActorRotation(NewRotation);
		//}
	}
}

void APlayerFight_Attacks::XBtnAction()
{
	UE_LOG(LogTemp, Warning, TEXT(" XBtnAction canAttack = %s"), canAttack ? TEXT("True") : TEXT("False"));

	if (isSuperMode && SpecialAttacknstance)
	{
		SpecialAttacknstance->GetPlayer(this);
		SpecialAttacknstance->XBtnActionSpe();
	}
	else
	{
		if (canAttack == true)
	{
		if (CurrentState == APlayerFight_States::EPlayerFight_State::Idle
			|| CurrentState == APlayerFight_States::EPlayerFight_State::Run
			|| CurrentState == APlayerFight_States::EPlayerFight_State::Sprint
			|| CurrentState == APlayerFight_States::EPlayerFight_State::Attack)
		{
			canMove = false;
			if (isMoving == true)
				isMoving = false;
			if (isIdle == true)
				isIdle = false;

			currentCombo++;
			if (currentCombo > comboLength)
			{
				currentCombo = 1;
				currentHit = 1;
			}
			if (currentCombo == comboLength)
				canFinalComboAttack = true;
			isAttacking = true;
			canAttack = false;
			isStrongAttacking = false;
			SetCharacterState(APlayerFight_States::EPlayerFight_State::Attack, 0.0f);
			timerWhenCanTurnAttacking = 10.0f;
			enemyTargetLock = PlayerFight_LockInstance->GetLastTarget();

			if (currentCombo == 1)
			{
				AttackOneNumber++;
				if (AttackOneNumber == 4)
					AttackOneNumber = 1;
			}
			else
				AttackOneNumber = 0;

			UE_LOG(LogTemp, Warning, TEXT("XBtnAction AttackOneNumber %d"), AttackOneNumber);
			//UE_LOG(LogTemp, Warning, TEXT("XBtnAction %d"), currentCombo);
			//UE_LOG(LogTemp, Warning, TEXT("XBtnAction currentCombo %d"), currentCombo);
			//UE_LOG(LogTemp, Warning, TEXT("XBtnAction currentAttack %d"), currentAttack);
			//UE_LOG(LogTemp, Warning, TEXT("XBtnAction isStrongAttacking = %s"), isStrongAttacking ? TEXT("True") : TEXT("False"));
		}
	}
	}
}

void APlayerFight_Attacks::YBtnAction()
{
	UE_LOG(LogTemp, Warning, TEXT(" YBtnAction canAttack = %s"), canAttack ? TEXT("True") : TEXT("False"));

	UE_LOG(LogTemp, Warning, TEXT(" YBtnAction canCounterAttack = %s"), canCounterAttack ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" YBtnAction CurrentState %d"), CurrentState);

	if (canCounterAttack && CurrentState == APlayerFight_States::EPlayerFight_State::Counter)
	{
		SetCharacterState(APlayerFight_States::EPlayerFight_State::CounterAttack, 0.0f);
		UE_LOG(LogTemp, Error, TEXT(" YBtnAction COUNTER ATTACK"));
		isStrongAttacking = true;
		SpecialAttacknstance->GetPlayer(this);
		SpecialAttacknstance->SpecialAttack();
		SpawnParticleSlow();
	}
	else if (SpecialAttacknstance)
	{
		if (isSuperMode)
		{
			if (canAttack == true)
			{
		
			}
			SpecialAttacknstance->GetPlayer(this);
			SpecialAttacknstance->YBtnActionSpe();
		}
		else
		{
			isStrongAttacking = true;
			SetCharacterState(APlayerFight_States::EPlayerFight_State::StanceSpe, 0.0f);
			UE_LOG(LogTemp, Warning, TEXT(" YBtnAction isStrongAttacking = %s"), isStrongAttacking ? TEXT("True") : TEXT("False"));
			SpecialAttacknstance->GetPlayer(this);
			SpecialAttacknstance->SpecialAttack();
		}
	}

}
void APlayerFight_Attacks::BBtnAction()
{
	UE_LOG(LogTemp, Warning, TEXT(" BBtnAction canCounterStance = %s"), canCounterStance ? TEXT("True") : TEXT("False"));
	if (isSuperMode && SpecialAttacknstance)
	{
		SpecialAttacknstance->GetPlayer(this);
		SpecialAttacknstance->BBtnActionSpe();
	}
	else
	{
		if (canCounterStance == true)
	{
		SetCharacterState(APlayerFight_States::EPlayerFight_State::CounterPose, 0.0f);
		canCounterStance = false;
		isCounterStance = true;
		isIdle = false;
		canMove = false;
		UE_LOG(LogTemp, Warning, TEXT(" BBtnAction isCounterStance = %s"), isCounterStance ? TEXT("True") : TEXT("False"));
	}
	}
}

void APlayerFight_Attacks::ABtnAction()
{
	UE_LOG(LogTemp, Warning, TEXT(" ABtnAction canCounterStance = %s"), canCounterStance ? TEXT("True") : TEXT("False"));
	if (isSuperMode && SpecialAttacknstance)
	{
		SpecialAttacknstance->GetPlayer(this);
		SpecialAttacknstance->ABtnActionSpe();
	}
	else
	{
		Super::ABtnAction();
	}
}

void APlayerFight_Attacks::DebugBtnAction()
{
	Super::DebugBtnAction();
	UE_LOG(LogTemp, Warning, TEXT(" currentCombo = %d"), currentCombo);
	UE_LOG(LogTemp, Warning, TEXT(" DebugBtnAction canAttack = %s"), canAttack ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" DebugBtnAction canMove = %s"), canMove ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" DebugBtnAction isMoving = %s"), isMoving ? TEXT("True") : TEXT("False"));

	UE_LOG(LogTemp, Warning, TEXT(" isDamaged = %s"), isDamaged ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" isRightAttack = %s"), isRightAttack ? TEXT("True") : TEXT("False"));
}

void APlayerFight_Attacks::HitCount()
{
	SpawnParticle();
	currentHit++;
}


void APlayerFight_Attacks::SpawnParticle()
{
	//UE_LOG(LogTemp, Warning, TEXT("SpawnParticle"));

	if (!AttackList.IsEmpty())
	{
		TSubclassOf<AActor> AttackClass = AttackList[currentHit];
		AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(AttackClass, GetActorLocation(), GetActorRotation());

		IIParticle_AttackEnemy* AttackInterface = Cast<IIParticle_AttackEnemy>(AttackInstance);

		if (AttackInterface)
		{
			AttackInterface->Execute_SetAttack(AttackInstance, Attack, isRightAttack);
		}
	}

}
void APlayerFight_Attacks::SpawnParticleSlow()
{

	if (SlowParticle)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnParticle SSLLLOOOWWW"));
		TSubclassOf<AActor> AttackClass = SlowParticle;
		AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(AttackClass, GetActorLocation(), GetActorRotation());

		IIParticle_AttackEnemy* AttackInterface = Cast<IIParticle_AttackEnemy>(AttackInstance);

		if (AttackInterface)
		{
			AttackInterface->Execute_SetAttack(AttackInstance, Attack, isRightAttack);
		}
	}

}


void APlayerFight_Attacks::SlowMotion(float slowStrength, int time)
{
	if(SpecialAttacknstance)
		SpecialAttacknstance->StartSlowMotion(slowStrength);
	slowMotionCooldown = time;
}
void APlayerFight_Attacks::DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, int damageCut)
{
	if (canBeHit && isCounterStance == false)
	{
		isRightAttack = isRightDamage;
		canBeHitCoolDown = 10.0f;
		canBeHit = false;

		currentDamageCut = currentDamageCut - damageCut;

		UE_LOG(LogTemp, Warning, TEXT("damageCut damageCut %d"), damageCut);
		UE_LOG(LogTemp, Warning, TEXT("CcurrentDamageCut currentDamageCut currentDamageCut %d"), currentDamageCut);
		UE_LOG(LogTemp, Warning, TEXT("isCutFromDamage isCutFromDamage = %s"), isCutFromDamage ? TEXT("True") : TEXT("False"));

		if (currentDamageCut <= 0 || isCutFromDamage == true)
		{
			isDamaged = true;

			SetCharacterState(APlayerFight_States::EPlayerFight_State::Damage, 0.0f);

			canMove = false;
			isMoving = false;
			isIdle = false;
			canAttack = false;
			currentCombo = 0;
			currentAttack = 0;
			isAttacking = false;

			isStartJump = false;
			isIdleJump = false;
			isDashJump = false;
			isDash = false;
			isNearGround = false;
			isSprint = false;
		}
		UE_LOG(LogTemp, Warning, TEXT("C'est le PLAYER qui prend des damage TakeDamage %d"), damage); 
	}
	if (isCounterStance)
	{
		SetCharacterState(APlayerFight_States::EPlayerFight_State::Counter, 0.0f);
		isCounterLeft = !isRightDamage;
		isCounter = true;

		currentCounterGauge +=10;
		if(currentCounterGauge > counterGaugeMax)
			currentCounterGauge = counterGaugeMax;

		UE_LOG(LogTemp, Warning, TEXT("C'est le PLAYER qui en pose COUNTER")); 
		UE_LOG(LogTemp, Warning, TEXT("DamageTake currentCounterGauge %f"), currentCounterGauge);
		SlowMotion(0.2f, 10);
	}

}
void APlayerFight_Attacks::Rotating() { Super::Rotating(); }
void APlayerFight_Attacks::RotatingFormDirection(FQuat InterpolatedRotationFormDirection )
{ Super::RotatingFormDirection(InterpolatedRotationFormDirection ); }

bool APlayerFight_Attacks::GetisAttacking()
{
	return isAttacking;
}
bool APlayerFight_Attacks::GetisStrongAttacking()
{
	return isStrongAttacking;
}
int APlayerFight_Attacks::GetcurrentCombo()
{
	return currentCombo;
}

bool APlayerFight_Attacks::GetisCounterStance()
{
	return isCounterStance;
}
bool APlayerFight_Attacks::GetisCounter()
{
	return isCounter;
}
bool APlayerFight_Attacks::GetisCounterLeft()
{
	return isCounterLeft;
}

bool APlayerFight_Attacks::GetisDamageRight()
{
	return isRightAttack;
}
bool APlayerFight_Attacks::GetisDamaged()
{
	return isDamaged;
}





void APlayerFight_Attacks::RemoveAllEnemy()
{
	UE_LOG(LogTemp, Warning, TEXT("RemoveAllEnemy ATTACK"));
	SpecialAttacknstance->RemoveAllEnemy();
}