// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Move.h"
#include "Math/RandomStream.h"
#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"


void AEnemy_Move::BeginPlay()
{
    Super::BeginPlay();

    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (PlayerCharacter)
    {
        //ActionChoice();
    }
    canBeHit = true;
    canCutAnimByDamage = true;
    isDamaged = false;
    hitCountDamageAnimation = 0;
    isDestinationPlayer;
    isSlow = false;
    canTurnToPlayer = false;

    currentHealth = Health;
    currentArmorValue = ArmorValue;
    armorRegenCoolDown = -1;
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
            UE_LOG(LogTemp, Log, TEXT(" canBeHitCoolDown canBeHitCoolDown FINI"));
            if (armorRegenCoolDown < 0)
                isDamaged = false;
        }
    }

    if (armorRegenCoolDown > 0)
    {
        armorRegenCoolDown--;
        if (armorRegenCoolDown == 0)
        {
            UE_LOG(LogTemp, Log, TEXT(" currentArmorValue FINI"));
            currentArmorValue = ArmorValue;
            armorRegenCoolDown = -1;
            WaitingForChoice();
        }
    }


    if (actionCooldown > -1)
    {
        actionCooldown--;
        //UE_LOG(LogTemp, Log, TEXT(" actionCooldown = %d"), actionCooldown);
        if (actionCooldown == 0)
        {
            UE_LOG(LogTemp, Error, TEXT(" FIN actionCooldown !!!!!!!! "));
            StopAction();
            WaitingForChoice();
        }
    }

    if (PlayerCharacter)
    {
        FVector PlayerLocation = PlayerCharacter->GetActorLocation();
        FVector EnemyLocation = GetActorLocation();

        distanceToPlayer = FVector::Distance(PlayerLocation, EnemyLocation);

        if (canMoveToPlace)
        {
            //UE_LOG(LogTemp, Warning, TEXT(" isDestinationPlayer = %s"), isDestinationPlayer ? TEXT("True") : TEXT("False"));
            if (isDestinationPlayer)
                DestinationtoMove = FVector(PlayerLocation.X, PlayerLocation.Y, 0.0f);

            distanceToMovePlace = FVector::Distance(DestinationtoMove, EnemyLocation);
            if (timeAction > 0 && distanceToMovePlace > 200)
            {

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
                if (canTrackToPlace == false)
                    WaitingForChoice();
                else
                    AttackPLayer();


                canMoveToPlace = false;
                canTrackToPlace = false;
                moveLR = 0.0f;
                moveFB = 0.0f;
            }

            //UE_LOG(LogTemp, Warning, TEXT(" PlayerLocation = %s"), *PlayerLocation.ToString());
            //UE_LOG(LogTemp, Warning, TEXT(" DestinationtoMove = %s"), *DestinationtoMove.ToString());
        }
        if (isWaiting)
        {
            //UE_LOG(LogTemp, Log, TEXT(" timeWaiting = %d"), timeWaiting);
            if (timeWaiting > 0)
                timeWaiting--;
            else
            {
                ActionChoice(); 
            }
        }

        if (isAttacking && canTurnToPlayer)
            LookAtPlayer();
    }

    if (isSlow)
    {
        if (slowMotionCountDown > 0)
            slowMotionCountDown--;
        else
        {
            isSlow = false;
            this->CustomTimeDilation = 1.0f;
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
    FVector RightVector = FRotationMatrix(EnemyRotation).GetScaledAxis(EAxis::Y); // Obtient le vecteur droit relatif Ela rotation

    float DirectionX = FVector::DotProduct(MovingDirection, ForwardVector);
    float DirectionY = FVector::DotProduct(MovingDirection, RightVector);

    moveLR = DirectionY;
    moveFB = DirectionX;
}



void AEnemy_Move::ActionChoice()
{
    isWaiting = false;
    int RandomInt = GenerateRandomInt(1, 100);
    if (RandomInt > 0 && RandomInt < 20)
    {
        ChoiceWaitingMove();
        actionCooldown = 100;
    }
    else if (RandomInt > 19 && RandomInt < 80)
    {
        ChoiceAttackPlayer();
        actionCooldown = 350;
    }
    else
    {
        ChoiceMoveToPlayer();
        isPlaceThePlayer = true;
        actionCooldown = 350;
    }
    //UE_LOG(LogTemp, Warning, TEXT(" canMoveToPlace = %s"), canMoveToPlace ? TEXT("True") : TEXT("False"));
    //UE_LOG(LogTemp, Warning, TEXT(" canTrackToPlace = %s"), canTrackToPlace ? TEXT("True") : TEXT("False"));
    //UE_LOG(LogTemp, Warning, TEXT(" isDamaged = %s"), isDamaged ? TEXT("True") : TEXT("False"));

    //UE_LOG(LogTemp, Warning, TEXT(" RandomInt = %d"), RandomInt);
}

void AEnemy_Move::WaitingForChoice()
{
    actionCooldown = -20;
    timeWaiting = GenerateRandomInt(1, 150);
    isWaiting = true;
    isPlaceThePlayer = false;
}



void AEnemy_Move::ChoiceMoveToPlayer()
{
    if (PlayerCharacter)
    {
        isDestinationPlayer = true;

        if (isPlaceThePlayer == false)
        {
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

        isDestinationPlayer = true;

        canMoveToPlace = true;
        canTrackToPlace = true;
        timeAction = 100;
    }
}


void AEnemy_Move::AttackPLayer(){}
void AEnemy_Move::Combo(){}


void AEnemy_Move::EndSlowMode()
{
    isSlow = false;
    this->CustomTimeDilation = 1.0f;
    slowMotionCountDown = 0;
}
void AEnemy_Move::ActivateSlowMode()
{
    isSlow = true;    
    this->CustomTimeDilation = 0.01f;
    slowMotionCountDown = 800;
}

void AEnemy_Move::SlowDownTake()
{
    if (isSlowDownTake == false)
    {
        isSlowDownTake = true;
        isDamaged = true;
        canMoveToPlace = false;
        canTrackToPlace = false;
        isWaiting = false;
    }
}
void AEnemy_Move::DamageTake(int damage, bool isRightDamage, float ArmorDamage)
{
    if (canBeHit)
    {
        hitCountDamageAnimation++;
        if (hitCountDamageAnimation == 4)
            hitCountDamageAnimation = 1;

        isRightAttackHit = isRightDamage;
        canBeHitCoolDown = 10.f;
        canBeHit = false;
        isDamaged = true;
        if (currentArmorValue > 0)
            currentArmorValue -= ArmorDamage;

        currentHealth -= damage;

        if (currentArmorValue <= 0)
        {
            if(armorRegenCoolDown <= 0)
                armorRegenCoolDown = 100;
            StopAction();
            /*
            UE_LOG(LogTemp, Warning, TEXT(" currentArmorValue < 0 "));
            UE_LOG(LogTemp, Warning, TEXT("ANIMATION ENEMY  isDamaged isDamaged = %s"), isDamaged ? TEXT("True") : TEXT("False"));
            */
        }
        UE_LOG(LogTemp, Error, TEXT("ANIMATION ENEMY  damage damage %f"), damage);
        UE_LOG(LogTemp, Log, TEXT("ANIMATION ENEMY  currentHealth currentHealth %f"), currentHealth);
        UE_LOG(LogTemp, Error, TEXT("ANIMATION ENEMY  ArmorDamage ArmorDamage %f"), ArmorDamage);
        UE_LOG(LogTemp, Log, TEXT("ANIMATION ENEMY  ArmorValue ArmorValue %f"), ArmorValue);

        //UE_LOG(LogTemp, Warning, TEXT("Enemy is Taking Damage"));
    }
}

void AEnemy_Move::EndArmorDamage()
{
    ChoiceWaitingMove();
}
void AEnemy_Move::StopAction()
{
    isWaiting = false;
    isDestinationPlayer = false;
    canMoveToPlace = false;
    //canTrackToPlace = false;
    isPlaceThePlayer = false;
}


float AEnemy_Move::GenerateRandomFloat(float Min, float Max)
{
    static FRandomStream RandomStreamFloat(FMath::Rand());
    float RandomFloatNumber = RandomStreamFloat.FRandRange(Min, Max);
    return RandomFloatNumber;
}
int AEnemy_Move::GenerateRandomInt(int Min, int Max)
{
    static FRandomStream RandomStreamInt(FMath::Rand());
    int RandomIntNumber = RandomStreamInt.FRandRange(Min, Max);
    return RandomIntNumber;
}

float AEnemy_Move::GetcurrentHealth()
{
    return currentHealth;
}
float AEnemy_Move::GetcurrentArmorValue()
{
    return currentArmorValue;
}
float AEnemy_Move::GetxMove()
{
    return moveLR * 100;
}
float AEnemy_Move::GetyMove()
{
    return moveFB * 100;
}
bool AEnemy_Move::GetisSlowDownTake()
{
    return isSlowDownTake;
}


