// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Move.h"
#include "Math/RandomStream.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"

AEnemy_Move::AEnemy_Move()
{
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (PlayerCharacter)
    {
        ActionChoice();
        //UE_LOG(LogTemp, Warning, TEXT("player is here"));
    }
    canBeHit = true;
    canCutAnimByDamage = true;
    isDamaged = false;
    hitCountDamageAnimation = 0;
    isDestinationPlayer;
}

void AEnemy_Move::BeginPlay()
{
    Super::BeginPlay();

}

void AEnemy_Move::Tick(float DeltaTime)
{ 
    Super::Tick(DeltaTime);

    if (canBeHit == false)
    {
        canBeHitCoolDown--;
        if (canBeHitCoolDown > 0)
        {
            canBeHit = true;
            //isDamaged = false;
        }
    }

    if (PlayerCharacter)
    {
        FVector PlayerLocation = PlayerCharacter->GetActorLocation();
        FVector EnemyLocation = GetActorLocation();

        distanceToPlayer = FVector::Distance(PlayerLocation, EnemyLocation);
        //UE_LOG(LogTemp, Warning, TEXT("distanceToPlayer %f"), distanceToPlayer);

        if (canMoveToPlace)
        {
            if (isDestinationPlayer)
                DestinationtoMove = FVector(PlayerLocation.X, PlayerLocation.Y, 0.0f);

            distanceToMovePlace = FVector::Distance(DestinationtoMove, EnemyLocation);
            if (timeAction > 0 && distanceToMovePlace > 200)
            {
               // UE_LOG(LogTemp, Warning, TEXT("distanceToMovePlace  %f"), distanceToMovePlace);
                //UE_LOG(LogTemp, Warning, TEXT("timeAction  %d"), timeAction);

                if (canTrackToPlace == false)
                    timeAction--;

                if(isDamaged == false)
                    MoveToPlace();

                if (isPlaceThePlayer && isDamaged == false)
                    ChoiceMoveToPlayer();

                if(isDamaged == false)
                    LookAtPlayer();
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("end"));
                UE_LOG(LogTemp, Warning, TEXT("canTrackToPlace  %d"), canTrackToPlace);


                if (canTrackToPlace == false)
                    WaitingForChoice();
                else
                    AttackPLayer();


                canMoveToPlace = false;
                canTrackToPlace = false;
                moveLR = 0.0f;
                moveFB = 0.0f;
            }
        }
        if (isWaiting)
        {
            if (timeWaiting > 0)
                timeWaiting--;
            else
            {
                ActionChoice(); 
                UE_LOG(LogTemp, Warning, TEXT("ActionChoice ActionChoice ActionChoice"));
            }
        }
    }

}


void AEnemy_Move::LookAtPlayer()
{
    if (PlayerCharacter)
    {
        FVector PlayerLocation = PlayerCharacter->GetActorLocation();
        FVector DirectionToPlayer = PlayerLocation - GetActorLocation();
        DirectionToPlayer.Z = 0.0f;
        FRotator LookAtRotation = FRotationMatrix::MakeFromX(DirectionToPlayer).Rotator();
        FRotator InterpolatedRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, GetWorld()->DeltaTimeSeconds, 10);
        SetActorRotation(InterpolatedRotation);
    }
}

void AEnemy_Move::MoveToPlace()
{
    FVector PreviousLocation;
    FVector CurrentLocation;

    PreviousLocation = GetActorLocation();

    FVector Direction = DestinationtoMove - GetActorLocation();
    Direction.Z = 0.0f;
    Direction.Normalize();

    FVector NewLocation = GetActorLocation() + Direction * 100 * GetWorld()->DeltaTimeSeconds;
    SetActorLocation(NewLocation);

    CurrentLocation = GetActorLocation();
    
    FVector MovingDirection = CurrentLocation - PreviousLocation;
    MovingDirection.Z = 0.0f; // Ignorer la composante z pour la direction horizontale
    MovingDirection.Normalize();

    FRotator EnemyRotation = GetActorRotation();
    FVector ForwardVector = EnemyRotation.Vector();
    FVector RightVector = FRotationMatrix(EnemyRotation).GetScaledAxis(EAxis::Y); // Obtient le vecteur droit relatif à la rotation

    float DirectionX = FVector::DotProduct(MovingDirection, ForwardVector);
    float DirectionY = FVector::DotProduct(MovingDirection, RightVector);

    moveLR = DirectionY;
    moveFB = DirectionX;
}



void AEnemy_Move::ActionChoice()
{
    isWaiting = false;
    int RandomInt = GenerateRandomInt(1, 100);


    //UE_LOG(LogTemp, Warning, TEXT("RandomInt  %d"), RandomInt);
    //UE_LOG(LogTemp, Warning, TEXT("isWaiting  %d"), isWaiting);
    //UE_LOG(LogTemp, Warning, TEXT("isPlaceThePlayer  %d"), isPlaceThePlayer);

    if (RandomInt > 0 && RandomInt < 20)
    {
        ChoiceWaitingMove();
    }
    else if (RandomInt > 19 && RandomInt < 80)
    {
        ChoiceAttackPlayer();
    }
    else
    {
        ChoiceMoveToPlayer();
        isPlaceThePlayer = true;
    }
}

void AEnemy_Move::WaitingForChoice()
{
    UE_LOG(LogTemp, Warning, TEXT("WaitingForChoice WaitingForChoice WaitingForChoice"));
    timeWaiting = GenerateRandomInt(1, 150);
    isWaiting = true;
    isPlaceThePlayer = false;
}



void AEnemy_Move::ChoiceMoveToPlayer()
{
    if (PlayerCharacter)
    {
        isDestinationPlayer = true;
        //UE_LOG(LogTemp, Warning, TEXT("ChoiceMoveToPlayer "));

        if (isPlaceThePlayer == false)
        {
           // UE_LOG(LogTemp, Warning, TEXT("isPlaceThePlayer "));
            canMoveToPlace = true;
            timeAction = 100;
        }
    }
}
void AEnemy_Move::ChoiceWaitingMove()
{
    isDestinationPlayer = false;
    FVector EnemyPosition = GetActorLocation();
    float Xvalue = GenerateRandomFloat(-300.0f, 300.0f);
    float Yvalue = GenerateRandomFloat(-300.0f, 300.0f);
    DestinationtoMove = FVector(EnemyPosition.X + Xvalue, EnemyPosition.Y + Yvalue, 0.0f);

    canMoveToPlace = true;
    timeAction = 100;
}
void AEnemy_Move::ChoiceAttackPlayer()
{
    if (PlayerCharacter)
    {
        FVector PlayerLocation = PlayerCharacter->GetActorLocation();
        DestinationtoMove = FVector(PlayerLocation.X, PlayerLocation.Y, 0.0f);

        //UE_LOG(LogTemp, Warning, TEXT("ChoiceAttackPlayer "));

        canMoveToPlace = true;
        canTrackToPlace = true;
        timeAction = 100;
    }
}


void AEnemy_Move::AttackPLayer(){}
void AEnemy_Move::Combo(){}




void AEnemy_Move::DamageTake(int damage, bool isRightDamage)
{
    if (canBeHit)
    {
        isRightAttackHit = isRightDamage;
        canBeHitCoolDown = 10.f;
        canBeHit = false;
        isDamaged = true;
        hitCountDamageAnimation++;
        if (hitCountDamageAnimation == 4)
        {
            hitCountDamageAnimation = 1;
        }
         UE_LOG(LogTemp, Warning, TEXT("hitCountDamageAnimation %d"), hitCountDamageAnimation);
    }
    UE_LOG(LogTemp, Warning, TEXT("TakeDamage %d"), damage);
}



float AEnemy_Move::GenerateRandomFloat(float Min, float Max)
{
    static FRandomStream RandomStreamFloat(FMath::Rand());
    float RandomFloatNumber = RandomStreamFloat.FRandRange(Min, Max);
    //UE_LOG(LogTemp, Warning, TEXT("RandomNumber %f"), RandomFloatNumber);
    return RandomFloatNumber;
}
int AEnemy_Move::GenerateRandomInt(int Min, int Max)
{
    static FRandomStream RandomStreamInt(FMath::Rand());
    int RandomIntNumber = RandomStreamInt.FRandRange(Min, Max);
    return RandomIntNumber;
}


float AEnemy_Move::GetxMove()
{
    return moveLR * 100;
}
float AEnemy_Move::GetyMove()
{
    return moveFB * 100;
}


