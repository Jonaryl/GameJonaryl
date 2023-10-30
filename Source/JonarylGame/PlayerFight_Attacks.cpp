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
	canStrongAttack = true;

	isCounterStance = false;
	isCounter = false;
	isCounterLeft = false;
	canCounterStance = true;
	canCounter = false;

	dashNumber = 0;
	counterNumber = 0;

	isRightAttack = true;
	isDamaged = false;
	canCounterAttack = false;
	canBeHit = true;
	canMoveWhenCombo = true;

	RootMotionProblem = false;

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
	}
	if (slowMotionCooldown > 2)
	{
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
		if(SpecialAttacknstance)
			SpecialAttacknstance->EndSlowMotion();
	}

	if(canBeHit == false && canBeHitCoolDown > -1)
	{
		//UE_LOG(LogTemp, Warning, TEXT(" doit pas passer par la = %d"), canBeHitCoolDown);

		canBeHitCoolDown--;
		if (canBeHitCoolDown < 0)
		{
			canCounterStance = true;
			canBeHit = true;
			isDamaged = false;

			UE_LOG(LogTemp, Error, TEXT(" End canBeHitCoolDown "));
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
	if (isSuperMode && SpecialAttacknstance && canStrongAttack == true)
	{
		canMove = false;
		if (isMoving == true)
			isMoving = false;
		if (isIdle == true)
			isIdle = false;

		canStrongAttack = false;
		SpecialAttacknstance->GetPlayer(this);
		SpecialAttacknstance->XBtnActionSpe();
		SetCharacterState(APlayerFight_States::EPlayerFight_State::AttackSpe, 0.0f);
	}
	else
	{
		if (canAttack == true)
		{
			if (CurrentState == APlayerFight_States::EPlayerFight_State::Idle
				|| CurrentState == APlayerFight_States::EPlayerFight_State::Run
				|| CurrentState == APlayerFight_States::EPlayerFight_State::Sprint
				|| CurrentState == APlayerFight_States::EPlayerFight_State::CounterPose
				|| CurrentState == APlayerFight_States::EPlayerFight_State::Attack)
			{
				RootMotionProblem = true;
				canStrongAttack = false;
				canMoveWhenCombo = false;

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
			}
		}
	}
}

void APlayerFight_Attacks::YBtnAction()
{
	if (canCounterAttack && CurrentState == APlayerFight_States::EPlayerFight_State::Counter)
	{
		SetCharacterState(APlayerFight_States::EPlayerFight_State::CounterAttack, 0.0f);
		isStrongAttacking = true;
		SpecialAttacknstance->GetPlayer(this);
		SpecialAttacknstance->SpecialAttack();
		SpawnParticleSlow();
	}
	else if (SpecialAttacknstance && isAttacking == false && canStrongAttack == true)
	{
		if (isSuperMode)
		{
			canMove = false;
			if (isMoving == true)
				isMoving = false;
			if (isIdle == true)
				isIdle = false;

			canStrongAttack = false;
			SpecialAttacknstance->GetPlayer(this);
			SpecialAttacknstance->YBtnActionSpe();
			SetCharacterState(APlayerFight_States::EPlayerFight_State::AttackSpe, 0.0f);
		}
		else
		{
			if (CurrentState == APlayerFight_States::EPlayerFight_State::Idle
				|| CurrentState == APlayerFight_States::EPlayerFight_State::Run)
			{
				isStrongAttacking = true;
				canStrongAttack = false;
				SetCharacterState(APlayerFight_States::EPlayerFight_State::StanceSpe, 0.0f);
				SpecialAttacknstance->GetPlayer(this);
				SpecialAttacknstance->SpecialAttack();
			}
		}
	}

}
void APlayerFight_Attacks::BBtnAction()
{
	if (CurrentState == APlayerFight_States::EPlayerFight_State::Run)
		canCounterStance = true;

	if (CurrentState != APlayerFight_States::EPlayerFight_State::IdleJump || CurrentState != APlayerFight_States::EPlayerFight_State::Jump || CurrentState != APlayerFight_States::EPlayerFight_State::DashJump || CurrentState != APlayerFight_States::EPlayerFight_State::Dash)
	{

		if (isSuperMode && SpecialAttacknstance && canStrongAttack == true)
		{
			canMove = false;
			if (isMoving == true)
				isMoving = false;
			if (isIdle == true)
				isIdle = false;

			canStrongAttack = false;
			SpecialAttacknstance->GetPlayer(this);
			SpecialAttacknstance->BBtnActionSpe();
			SetCharacterState(APlayerFight_States::EPlayerFight_State::AttackSpe, 0.0f);
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT(" canCounterStance = %s"), canCounterStance ? TEXT("True") : TEXT("False"));
			//UE_LOG(LogTemp, Warning, TEXT(" canBeHit = %s"), canBeHit ? TEXT("True") : TEXT("False"));
			//UE_LOG(LogTemp, Warning, TEXT(" isDle = %s"), isIdle ? TEXT("True") : TEXT("False"));
			if (canCounterStance == true)
			{
				SetCharacterState(APlayerFight_States::EPlayerFight_State::CounterPose, 0.0f);
				canCounterStance = false;
				isIdle = false;
				canMove = false;
				canDash = false;
				canAttack = false;
				isCounterStance = true;

				counterNumber++;
				if (counterNumber == 4)
					counterNumber = 1;
			}
		}
	}
}

void APlayerFight_Attacks::ABtnAction()
{
	if (isSuperMode && SpecialAttacknstance && canStrongAttack == true)
	{
		canStrongAttack = false;
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

void APlayerFight_Attacks::StopCombo()
{
	canCounterStance = false;
	canAttack = false;
	currentCombo = 0;
	currentAttack = 0;
	currentHit = 0;
	isAttacking = false;
	isStrongAttacking = false;
}
void APlayerFight_Attacks::HitCount()
{
	SpawnParticle();
	currentHit++;
}


void APlayerFight_Attacks::SpawnParticle()
{
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
		TSubclassOf<AActor> AttackClass = SlowParticle;
		AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(AttackClass, GetActorLocation(), GetActorRotation());

		IIParticle_AttackEnemy* AttackInterface = Cast<IIParticle_AttackEnemy>(AttackInstance);

		if (AttackInterface)
		{
			AttackInterface->Execute_SetAttack(AttackInstance, Attack, isRightAttack);
		}
	}

}
void APlayerFight_Attacks::SpawnParticleCounter(bool isRightDamage, AActor* Enemy)
{
	if (CounterParticleL && CounterParticleR)
	{
		TSubclassOf<AActor> AttackClass;
		if (isRightDamage)
			AttackClass = CounterParticleR;
		else
			AttackClass = CounterParticleL;

		AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(AttackClass, GetActorLocation(), GetActorRotation());

		IIParticle_AttackEnemy* AttackInterface = Cast<IIParticle_AttackEnemy>(AttackInstance);

		if (AttackInterface)
		{
			AttackInterface->Execute_IsCountered(AttackInstance, Enemy);
		}
	}
}


void APlayerFight_Attacks::SlowMotion(float slowStrength, int time)
{
	if(SpecialAttacknstance)
		SpecialAttacknstance->StartSlowMotion(slowStrength);
	slowMotionCooldown = time;
}
void APlayerFight_Attacks::DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, int damageCut, AActor* Enemy)
{
	counterNumber = 0;
	UE_LOG(LogTemp, Warning, TEXT(" canBeHit = %s"), canBeHit ? TEXT("True") : TEXT("False"));
	if (canBeHit && isCounterStance == false)
	{
		isRightAttack = isRightDamage;
		canBeHitCoolDown = 10.0f;
		canBeHit = false;

		currentDamageCut = currentDamageCut - damageCut;

		UE_LOG(LogTemp, Warning, TEXT("Damage"));

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
	}
	if (isCounterStance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Counter"));

		SetCharacterState(APlayerFight_States::EPlayerFight_State::Counter, 0.0f);
		isCounterLeft = !isRightDamage;
		isCounter = true;
		canBeHit = false;

		canBeHitCoolDown = 10.0f;

		currentCounterGauge +=10;
		if(currentCounterGauge > counterGaugeMax)
			currentCounterGauge = counterGaugeMax;

		SpawnParticleCounter(isRightDamage, Enemy);
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
	SpecialAttacknstance->RemoveAllEnemy();
}