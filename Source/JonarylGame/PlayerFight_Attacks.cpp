// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Attacks.h"


void APlayerFight_Attacks::BeginPlay()
{
	Super::BeginPlay();
	currentCombo = 0;
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

}

void APlayerFight_Attacks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState == APlayerFight_States::EPlayerFight_State::Attack)
	{
		//UE_LOG(LogTemp, Warning, TEXT("attack move"));
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
	if (canAttack == true)
	{
		if (CurrentState == APlayerFight_States::EPlayerFight_State::Idle
			|| CurrentState == APlayerFight_States::EPlayerFight_State::Run
			|| CurrentState == APlayerFight_States::EPlayerFight_State::Sprint
			|| CurrentState == APlayerFight_States::EPlayerFight_State::Attack)
		{
			currentCombo++;
			if (currentCombo > 5)
				currentCombo = 1;
			if (currentCombo == 5)
				canFinalComboAttack = true;
			isAttacking = true;
			canAttack = false;
			isStrongAttacking = false;
			SetCharacterState(APlayerFight_States::EPlayerFight_State::Attack, 0.0f);

			//UE_LOG(LogTemp, Warning, TEXT("XBtnAction %d"), currentCombo);
			//UE_LOG(LogTemp, Warning, TEXT("XBtnAction currentCombo %d"), currentCombo);
			//UE_LOG(LogTemp, Warning, TEXT("XBtnAction currentAttack %d"), currentAttack);
			//UE_LOG(LogTemp, Warning, TEXT("XBtnAction isStrongAttacking = %s"), isStrongAttacking ? TEXT("True") : TEXT("False"));
		}
	}
}

void APlayerFight_Attacks::YBtnAction()
{
	UE_LOG(LogTemp, Warning, TEXT(" YBtnAction canAttack = %s"), canAttack ? TEXT("True") : TEXT("False"));
	if (canAttack == true)
	{
		if (CurrentState == APlayerFight_States::EPlayerFight_State::Idle
			|| CurrentState == APlayerFight_States::EPlayerFight_State::Run
			|| CurrentState == APlayerFight_States::EPlayerFight_State::Sprint
			|| CurrentState == APlayerFight_States::EPlayerFight_State::Attack)
		{
			currentCombo++;
			if (currentCombo > 5 && canFinalComboAttack == true || currentCombo < 6 && canFinalComboAttack == false)
			{
				isStrongAttacking = true;
				isAttacking = true;
				canAttack = false;
				SetCharacterState(APlayerFight_States::EPlayerFight_State::Attack, 0.0f);

				//UE_LOG(LogTemp, Warning, TEXT("YBtnAction %d"), currentCombo);
				//UE_LOG(LogTemp, Warning, TEXT("YBtnAction currentCombo %d"), currentCombo);
				//UE_LOG(LogTemp, Warning, TEXT("YBtnAction currentAttack %d"), currentAttack);
				//UE_LOG(LogTemp, Warning, TEXT(" YBtnAction isStrongAttacking = %s"), isStrongAttacking ? TEXT("True") : TEXT("False"));
			}
			else
				currentCombo = 1;
		}
	}
}
void APlayerFight_Attacks::BBtnAction()
{
	UE_LOG(LogTemp, Warning, TEXT(" BBtnAction canCounterStance = %s"), canCounterStance ? TEXT("True") : TEXT("False"));
	if (canCounterStance == true)
	{
		SetCharacterState(APlayerFight_States::EPlayerFight_State::CounterPose, 0.0f);
		canCounterStance = false;
		isCounterStance = true;
		UE_LOG(LogTemp, Warning, TEXT(" BBtnAction isCounterStance = %s"), isCounterStance ? TEXT("True") : TEXT("False"));
	}
}

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