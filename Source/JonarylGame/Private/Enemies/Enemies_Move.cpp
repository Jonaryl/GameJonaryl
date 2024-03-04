// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemies_Move.h"

#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"

	/////////////////////////// BASE METHOD ///////////////////////////

void AEnemies_Move::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	CollisionEnemy = AEnemies_Move::FindComponentByClass<UBoxComponent>();
	if (CollisionEnemy) { }
}
void AEnemies_Move::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


/////////////////////////// MOVING ///////////////////////////
void AEnemies_Move::Moving(FVector destinationToGo)
{

	FVector PreviousLocation;
	FVector CurrentLocation;

	PreviousLocation = GetActorLocation();

	FVector Direction = destinationToGo - GetActorLocation();
	Direction.Z = 0.0f;
	Direction.Normalize();

	isMoving = true;
	float speed = 1.0f;
	if (CurrentActionState == EStates_EnemiesActions::Run)
	{
		speed = maxRunSpeed;
		isRuning = true;
	}
	else if (CurrentActionState == EStates_EnemiesActions::Sprint)
	{
		speed = maxSprintSpeed;
		isRuning = true;
	}
	else
	{
		speed = maxWalkSpeed;
		isRuning = false;
	}
		
	FVector NewLocation = GetActorLocation() + Direction * (speed * 10) * GetWorld()->DeltaTimeSeconds;
	SetActorLocation(NewLocation);

	CurrentLocation = GetActorLocation();

	GetxyMovingValue(PreviousLocation, CurrentLocation);
}

void AEnemies_Move::Turning(FVector destinationToLookAt, float speed)
{
	FVector DirectionToLook = destinationToLookAt - GetActorLocation();
	DirectionToLook.Z = 0.0f;
	FRotator LookAtRotation = FRotationMatrix::MakeFromX(DirectionToLook).Rotator();
	FRotator InterpolatedRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, GetWorld()->DeltaTimeSeconds, runRotationSpeed * speed);

	SetActorRotation(InterpolatedRotation);
}

FVector AEnemies_Move::GetPlacePosition()
{
	FVector EnemyPosition = GetActorLocation();
	float Xvalue = GenerateRandomFloat(-distanceToMovePlace, distanceToMovePlace);
	float Yvalue = GenerateRandomFloat(-distanceToMovePlace/2, distanceToMovePlace);
	FVector PlaceLocation = FVector(EnemyPosition.X + Xvalue, EnemyPosition.Y + Yvalue, 0.0f);

	return PlaceLocation;
}
float AEnemies_Move::GetPlaceDistance(FVector place)
{
	FVector EnemyLocation = GetActorLocation();

	float playerDistance = FVector::Distance(place, EnemyLocation);

	return playerDistance;
}
////////////// MOVING ANIMATION METHOD /////////////
void AEnemies_Move::GetxyMovingValue(FVector previousPosition, FVector nextPosition)
{
	FVector MovingDirection = nextPosition - previousPosition;
	MovingDirection.Z = 0.0f; // Ignorer la composante z pour la direction horizontale
	MovingDirection.Normalize();

	FRotator EnemyRotation = GetActorRotation();
	FVector ForwardVector = EnemyRotation.Vector();
	FVector RightVector = FRotationMatrix(EnemyRotation).GetScaledAxis(EAxis::Y); // Obtient le vecteur droit relatif Ela rotation

	float DirectionX = FVector::DotProduct(MovingDirection, ForwardVector);
	float DirectionY = FVector::DotProduct(MovingDirection, RightVector);

	xyMovingValue = FVector(DirectionX, DirectionY, 0);
}





/////////////////////////// PLAYER INFO ///////////////////////////
FVector AEnemies_Move::GetPlayerPosition()
{
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	return PlayerLocation;
}

float AEnemies_Move::GetPlayerDistance()
{
	FVector PlayerLocation = GetPlayerPosition();
	FVector EnemyLocation = GetActorLocation();

	float playerDistance = FVector::Distance(PlayerLocation, EnemyLocation);

	return playerDistance;
}

void AEnemies_Move::SetPlayerState(UStates_PlayerF::EStates_PlayerF playerStates)
{
	CurrentPlayerState = playerStates;
	ReactionToPlayer();
}




/////////////////////////// STATES ///////////////////////////
	////ACTIONS/////
void AEnemies_Move::SetActionState(EStates_EnemiesActions NewState, float Time)
{
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;
	TimerDel.BindUObject(this, &AEnemies_Move::ChangeActionState, NewState);
	if (Time == 0.0f)
		AEnemies_Move::ChangeActionState(NewState);
	else
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, Time, false);
}
void AEnemies_Move::ChangeActionState(EStates_EnemiesActions NewState)
{
	CurrentActionState = NewState;
}

////BEHAVIOURS/////
void AEnemies_Move::SetBehaviorState(EStates_EnemiesBehaviors NewState, float Time)
{
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDel;
	TimerDel.BindUObject(this, &AEnemies_Move::ChangeBehaviorState, NewState);
	if (Time == 0.0f)
		AEnemies_Move::ChangeBehaviorState(NewState);
	else
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, Time, false);
}
void AEnemies_Move::ChangeBehaviorState(EStates_EnemiesBehaviors NewState)
{
	CurrentBehaviorsState = NewState;
}


/////////////////////////////// TOOLS  ////////////////////////////////

float AEnemies_Move::GenerateRandomFloat(float Min, float Max)
{
	static FRandomStream RandomStreamFloat(FMath::Rand());
	float RandomFloatNumber = RandomStreamFloat.FRandRange(Min, Max);
	return RandomFloatNumber;
}
int AEnemies_Move::GenerateRandomInt(int Min, int Max)
{
	static FRandomStream RandomStreamInt(FMath::Rand());
	int RandomIntNumber = RandomStreamInt.FRandRange(Min, Max);
	return RandomIntNumber;
}
/////////////////////////// DELEGATE ///////////////////////////
void AEnemies_Move::ReactionToPlayer() {}
void AEnemies_Move::StopAllActions() {}
void AEnemies_Move::NewAction() {}

/////////////////////////// SEND MESSAGES ///////////////////////////
void AEnemies_Move::SetIds(int currentId, int currentIdZone, int currentIdWave) 
{
	id = currentId;
	idZone = currentIdZone;
	idWave = currentIdWave;
}

