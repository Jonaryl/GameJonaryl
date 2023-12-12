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
	damageAnimNumber = 0;
	counterNumber = 0;
	counterCooldown = 0.0f;

	isRightAttack = true;
	isDamaged = false;
	canCounterAttack = false;
	isCounterAttacking = false;
	canBeHit = true;
	canMoveWhenCombo = true;

	RootMotionProblem = false;

	canCounterStanceCombo = false;

	currentDamageCut = cutDamageStamina;

	if (SpecialAttack)
	{
		SpecialAttacknstance = NewObject<UPlayerFight_SpecialAttack>(this, SpecialAttack);
	}
	PostProcessSlow = FindComponentByClass<UPostProcessComponent>();

	if (PostProcessSlow)
		PostProcessSlowActivate(false); 
}

void APlayerFight_Attacks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentDamageCut <= cutDamageStamina)
	{
		currentDamageCut++;
	}

	//UE_LOG(LogTemp, Warning, TEXT("canCounterStance %s"), canCounterStance ? TEXT("True") : TEXT("False"));

	if (counterCooldown >= 0)
	{
		counterCooldown--;
		if (isCounter && isAttacking == false)
		{
			if (counterCooldown > 0)
				isCounterStance = true;
			else
				isCounterStance = false;
		}
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
			if (CurrentState == APlayerFight_States::EPlayerFight_State::Damage)
			{
				//UE_LOG(LogTemp, Log, TEXT(" CurrentState == APlayerFight_States::EPlayerFight_State::Damage "));
				canCounterStance = true;
			}
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
	//UE_LOG(LogTemp, Warning, TEXT(" XBtnAction canAttack = %s"), canAttack ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Warning, TEXT(" XBtnAction currentState = %d"), CurrentState);

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
		atkSpeChoice = 2;
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
				|| CurrentState == APlayerFight_States::EPlayerFight_State::Counter
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

				if (isCounterStance == true)
					isCounterStance = false;

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
				//UE_LOG(LogTemp, Error, TEXT(" XBtnAction canAttack = false; "));
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
	UE_LOG(LogTemp, Warning, TEXT(" currentState = %d"), CurrentState);
	if (canCounterAttack && CurrentState == APlayerFight_States::EPlayerFight_State::Counter)
	{
		StopCombo();
		SetCharacterState(APlayerFight_States::EPlayerFight_State::CounterAttack, 0.0f);
		isStrongAttacking = true;
		isCounterAttacking = true;
		SpecialAttacknstance->GetPlayer(this);
		SpecialAttacknstance->SpecialAttack();
		SpawnParticleSlow();
		UE_LOG(LogTemp, Error, TEXT(" CounterAttack"));
		UE_LOG(LogTemp, Warning, TEXT(" isCounterAttacking isCounterAttacking isCounterAttacking isCounterAttacking = %s"), isCounterAttacking ? TEXT("True") : TEXT("False"));
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
			atkSpeChoice = 3;
			SetCharacterState(APlayerFight_States::EPlayerFight_State::AttackSpe, 0.0f);
		}
		else
		{
			if (CurrentState == APlayerFight_States::EPlayerFight_State::Idle
				|| CurrentState == APlayerFight_States::EPlayerFight_State::Run)
			{
				UE_LOG(LogTemp, Error, TEXT(" isSuperMode"));
				isStrongAttacking = true;
				canStrongAttack = false;
				isCounterAttacking = false;
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

	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction __________________________________________"));
	//UE_LOG(LogTemp, Error, TEXT(" SpecialAttacknstance = %s"), SpecialAttacknstance ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Error, TEXT(" XBtnAction hasLanded = true; = %s"), hasLanded ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction canAttack = %s"), canAttack ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction currentState = %d"), CurrentState);
	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction canMove = true; = %s"), canMove ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction isAttacking = false; = %s"), isAttacking ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction isStrongAttacking = false; = %s"), isStrongAttacking ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction isCounter = false; = %s"), isCounter ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction canStrongAttack = true; = %s"), canStrongAttack ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction isStartJump = false; = %s"), isStartJump ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction isIdleJump = false; = %s"), isIdleJump ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction isDashJump = false; = %s"), isDashJump ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction isDash = false; = %s"), isDash ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Error, TEXT(" XBtnAction canDash = true; = %s"), canDash ? TEXT("True") : TEXT("False"));
	//UE_LOG(LogTemp, Log, TEXT(" XBtnAction __________________________________________"));
	if (CurrentState != APlayerFight_States::EPlayerFight_State::IdleJump 
		|| CurrentState != APlayerFight_States::EPlayerFight_State::Jump 
		|| CurrentState != APlayerFight_States::EPlayerFight_State::DashJump 
		|| CurrentState != APlayerFight_States::EPlayerFight_State::Dash)
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
			atkSpeChoice = 1;
			SetCharacterState(APlayerFight_States::EPlayerFight_State::AttackSpe, 0.0f);
		}
		else
		{
			if (canCounterStance == true)
			{
	/*			UE_LOG(LogTemp, Error, TEXT(" isIdle = %s"), isIdle ? TEXT("True") : TEXT("False"));
				UE_LOG(LogTemp, Log, TEXT(" XBtnAction counterNumber = %d"), counterNumber);
				UE_LOG(LogTemp, Log, TEXT(" BBtnActionBBtnActionBBtnAction canCounterStance = %s"), canCounterStance ? TEXT("True") : TEXT("False")); 
				UE_LOG(LogTemp, Log, TEXT(" BBtnAction currentState = %d"), CurrentState);*/
				UE_LOG(LogTemp, Warning, TEXT(" currentState = %d"), CurrentState);
				canCounterStanceCombo = false;
				if (CurrentState == APlayerFight_States::EPlayerFight_State::Counter)
				{
					counterNumber = 5;
					canCounterStanceCombo = true;
					UE_LOG(LogTemp, Warning, TEXT("_____ CurrentState == APlayerFight_States::EPlayerFight_State::Counter _____"));
				}

				SetCharacterState(APlayerFight_States::EPlayerFight_State::CounterPose, 0.0f);
				canCounterStance = false;

				isCounter = false;
				isIdle = false;
				canMove = false;
				canDash = false;
				canAttack = false;
				isCounterStance = true;

				isAttacking = false;
				isStrongAttacking = false;

				AttackOneNumber = 0;

				counterNumber++;
				if (counterNumber == 4 || counterNumber == 7)
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
		atkSpeChoice = 0;
		SpawnParticleAtkSpe();
		PostProcessSlowActivate(false);
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
	UE_LOG(LogTemp, Warning, TEXT(" counterNumber = %d"), counterNumber);
	UE_LOG(LogTemp, Warning, TEXT(" currentAttack = %d"), currentAttack);
	UE_LOG(LogTemp, Warning, TEXT(" currentHit = %d"), currentHit);
	UE_LOG(LogTemp, Warning, TEXT(" canBeHitCoolDown = %d"), canBeHitCoolDown);
	UE_LOG(LogTemp, Warning, TEXT(" currentCounterGauge = %d"), currentCounterGauge);
	UE_LOG(LogTemp, Warning, TEXT(" counterCooldown = %d"), counterCooldown);
	UE_LOG(LogTemp, Warning, TEXT(" DebugBtnAction canAttack = %s"), canAttack ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" DebugBtnAction canMove = %s"), canMove ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" DebugBtnAction isMoving = %s"), isMoving ? TEXT("True") : TEXT("False"));

	UE_LOG(LogTemp, Warning, TEXT(" isDamaged = %s"), isDamaged ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" isRightAttack = %s"), isRightAttack ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" canCounterStance = %s"), canCounterStance ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" isCounter = %s"), isCounter ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" canDash = %s"), canDash ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" isCounterStance = %s"), isCounterStance ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" canCounterStanceCombo = %s"), canCounterStanceCombo ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" isAttacking = %s"), isAttacking ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" isStrongAttacking = %s"), isStrongAttacking ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" isCounterLeft = %s"), isCounterLeft ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" canBeHit = %s"), canBeHit ? TEXT("True") : TEXT("False"));
	UE_LOG(LogTemp, Warning, TEXT(" isDamaged = %s"), isDamaged ? TEXT("True") : TEXT("False"));
}

void APlayerFight_Attacks::StopCombo()
{
	canCounterStance = false;
	canAttack = false;
	//UE_LOG(LogTemp, Error, TEXT(" StopCombo canAttack = false; "));
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
void APlayerFight_Attacks::LaunchParticleSpe()
{
	SpawnParticleAtkSpe();
}


void APlayerFight_Attacks::SpawnParticleAtkSpe()
{
	if (!AttackSpeList.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT(" isActivate isActivate isActivate isActivate = %d"), atkSpeChoice);
		if (atkSpeChoice < 5 && atkSpeChoice > -1)
		{
			UE_LOG(LogTemp, Warning, TEXT(" atkSpeChoice < 5 && atkSpeChoice > -1 "));
			TSubclassOf<AActor> AttackClass = AttackSpeList[atkSpeChoice];
			
			AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(AttackClass, GetActorLocation(), GetActorRotation());

			IIParticle_AttackEnemy* AttackInterface = Cast<IIParticle_AttackEnemy>(AttackInstance);

			if (AttackInterface)
			{
				AttackInterface->Execute_SetAttack(AttackInstance, Attack, isRightAttack, this);
			}
		}
	}
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
			AttackInterface->Execute_SetAttack(AttackInstance, Attack, isRightAttack, this);
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
			AttackInterface->Execute_SetAttack(AttackInstance, Attack, isRightAttack, this);
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


void APlayerFight_Attacks::PostProcessSlowActivate(bool isActivate)
{
	UE_LOG(LogTemp, Warning, TEXT(" isActivate = %s"), isActivate ? TEXT("True") : TEXT("False"));
	PostProcessSlow->bEnabled = isActivate;
}

void APlayerFight_Attacks::SlowMotion(float slowStrength, int time)
{
	if(SpecialAttacknstance)
		SpecialAttacknstance->StartSlowMotion(slowStrength);
	slowMotionCooldown = time;
}
void APlayerFight_Attacks::DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, int damageCut, AActor* Enemy)
{
	//counterNumber = 0;
	if (canBeHit && isCounterStance == false)
	{
		isRightAttack = isRightDamage;
		canBeHitCoolDown = 10.0f;
		canBeHit = false;

		currentDamageCut = currentDamageCut - damageCut;

		//UE_LOG(LogTemp, Warning, TEXT("Damage"));

		if (currentDamageCut <= 0 || isCutFromDamage == true)
		{
			StopCombo();

			isDamaged = true; 
			damageAnimNumber++;
			if (damageAnimNumber == 4)
				damageAnimNumber = 1;

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
		//UE_LOG(LogTemp, Warning, TEXT("Counter"));
 
		SetCharacterState(APlayerFight_States::EPlayerFight_State::Counter, 0.0f);
		isCounterLeft = !isRightDamage;
		isCounter = true;
		canBeHit = false;
		canAttack = false;

		canBeHitCoolDown = 10.0f;

		currentCounterGauge += 10;
		counterCooldown = 36.0f;

		AttackOneNumber = 0;

		if(currentCounterGauge > counterGaugeMax)
			currentCounterGauge = counterGaugeMax;

		SpawnParticleCounter(isRightDamage, Enemy);
		SlowMotion(0.2f, 10);

		//UE_LOG(LogTemp, Log, TEXT(" isCounter = %s"), isCounter ? TEXT("True") : TEXT("False"));
		//UE_LOG(LogTemp, Log, TEXT(" isCounterLeft = %s"), isCounterLeft ? TEXT("True") : TEXT("False"));

		//UE_LOG(LogTemp, Log, TEXT(" hasLanded = %s"), hasLanded ? TEXT("True") : TEXT("False"));
		//UE_LOG(LogTemp, Log, TEXT(" canCounterStanceCombo = %s"), canCounterStanceCombo ? TEXT("True") : TEXT("False"));
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