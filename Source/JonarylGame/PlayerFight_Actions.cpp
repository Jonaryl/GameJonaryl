// Fill out your copyright notice in the Description page of Project Settings.


#include  "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerFight_Actions.h"

APlayerFight_Actions::APlayerFight_Actions()
{
    PrimaryActorTick.bCanEverTick = true;

}

void APlayerFight_Actions::BeginPlay()
{
    Super::BeginPlay();

    // Initialisez le contrôleur de personnage

}

// Called every frame
void APlayerFight_Actions::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentState == APlayerFight_States::EPlayerFight_State::Jump) 
    {
        loopTurn++;
        JumpAction();
        ActionTurn(false);
        if (loopTurn == 25)
        {
            isStartJump = false;
            isIdleJump = true;
            SetCharacterState(APlayerFight_States::EPlayerFight_State::IdleJump, 0.0f);
            CancelGravity();
        }
    }
    if (CurrentState == APlayerFight_States::EPlayerFight_State::IdleJump && loopTurn >= 0)
    {
        loopTurn--;
        JumpDown();
        ActionTurn(false);
    }
    if (CurrentState == APlayerFight_States::EPlayerFight_State::DashJump)
    {
        loopTurn++;
        JumpDown();
        ActionTurn(true);
    }
    if (CurrentState == APlayerFight_States::EPlayerFight_State::Dash)
    {
        loopTurn++;
        DashAction();
        ActionTurn(true);
        if (loopTurn < 35 && loopTurn > 30 && isNearGround == true && isSprintInput == true && isMoveInput == true)
        {
            SetCharacterState(APlayerFight_States::EPlayerFight_State::Sprint, 0.0f);
            isDash = false;
            canDash = true;
            isSprint = true;
        }
        else if (loopTurn < 35 && loopTurn > 30 && isNearGround == true && isSprintInput == false && isMoveInput == true)
        {
            SetCharacterState(APlayerFight_States::EPlayerFight_State::Run, 0.0f);
            isDash = false;
            canDash = true;
            isSprint = false;
        }
        if (loopTurn == 35)
        {
            isStartJump = false;
            isIdleJump = true;
            if (isNearGround == false)
                SetCharacterState(APlayerFight_States::EPlayerFight_State::IdleJump, 0.0f);
            else if (isSprintInput == true && isMoveInput == true)
                SetCharacterState(APlayerFight_States::EPlayerFight_State::Sprint, 0.0f);
            else if (isSprintInput == false && isMoveInput == true)
                SetCharacterState(APlayerFight_States::EPlayerFight_State::Run, 0.0f);
            else
                SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle, 0.0f);
            isDash = false;
            canDash = true;
            CancelGravity();
        }
    }

    /////////////////// raycast ///////////////////////////////////////////////////////// 
    if (CurrentState == APlayerFight_States::EPlayerFight_State::DashJump || CurrentState == APlayerFight_States::EPlayerFight_State::IdleJump || CurrentState == APlayerFight_States::EPlayerFight_State::Dash
        || CurrentState == APlayerFight_States::EPlayerFight_State::Idle && isNearGround == false
        || CurrentState == APlayerFight_States::EPlayerFight_State::Run && isNearGround == false)
    {

        float GroundCheckDistance = 3000.0f;
        FVector StartLocation = GetActorLocation();
        FVector EndLocation = StartLocation - FVector(0.0f, 0.0f, GroundCheckDistance);
        FHitResult HitResult;
        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(this);

        DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 0.1f, 0, 2.0f);
        bIsGrounded = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams);

        if (bIsGrounded)
        {
            float oldDistanceToGround = DistanceToGround;
            DistanceToGround = HitResult.Distance;

            /*
            if (DistanceToGround < oldDistanceToGround && DistanceToGround > 150)
            {
                isIdleJump = true;
            }
            */
            
            if (DistanceToGround < 150)
            {
                //UE_LOG(LogTemp, Warning, TEXT(" DistanceToGround ") );
                isNearGround = true;
                isDashJump = false;
            }
            else
                isNearGround = false;
        }
    }
    /////////////////// raycast ///////////////////////////////////////////////////////// 
}

void APlayerFight_Actions::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}



void APlayerFight_Actions::ABtnAction()
{
    UE_LOG(LogTemp, Warning, TEXT("CurrentState %d"), CurrentState);
    if (CurrentState != APlayerFight_States::EPlayerFight_State::Jump && CurrentState != APlayerFight_States::EPlayerFight_State::IdleJump && 
        CurrentState != APlayerFight_States::EPlayerFight_State::DashJump && CurrentState != APlayerFight_States::EPlayerFight_State::Dash)
    {
        if (PlayerController->GetCharacter() && PlayerController->GetCharacter()->GetCharacterMovement()) 
        {
            XMoveDirection = 0.0f;
            YMoveDirection = 0.0f;
            SetCharacterState(APlayerFight_States::EPlayerFight_State::Jump, 0.0f);
            UE_LOG(LogTemp, Warning, TEXT("Jump "));
            isStartJump = true;
            isNearGround = false;
            loopTurn = 0;
        }
        else {
            UE_LOG(LogTemp, Error, TEXT("PlayerMesh is null"));
        }
    }
    else if (CurrentState == APlayerFight_States::EPlayerFight_State::IdleJump || CurrentState == APlayerFight_States::EPlayerFight_State::Jump)
    {
        if (isNearGround == false)
        {
            if (PlayerController->GetCharacter() && PlayerController->GetCharacter()->GetCharacterMovement())
            {
                UE_LOG(LogTemp, Error, TEXT("DashJump"));
                loopTurn = 0;
                SetCharacterState(APlayerFight_States::EPlayerFight_State::DashJump, 0.0f);
                isDashJump = true;
                isStartJump = false;
            }
            else {
                UE_LOG(LogTemp, Error, TEXT("PlayerMesh is null"));
            }
        }
    }
}


void APlayerFight_Actions::JumpAction()
{
    int sens = 1;
    const FVector upvector = GetActorUpVector();

    int upSpeed[25]{ 
        4000000.0f, 3000000.0f, 800000.0f, 600000.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 
        -100000.0f, -200000.0f, -300000.0f, -400000.0f, -1000000.0f, -1500000.0f
    };

    const FVector relativeMoveVector = FVector(XMoveDirection*20, -YMoveDirection*20, 0);
    FVector worldMoveVector = GetActorRotation().RotateVector(relativeMoveVector);

    if (loopTurn == 8)
        sens = -1;

    const FVector force = ((upvector * sens ) *upSpeed[loopTurn])+ (worldMoveVector * 1000);

    PlayerController->GetCharacter()->GetCharacterMovement()->AddForce(force);
}


void APlayerFight_Actions::JumpDown()
{
    const FVector upvector = GetActorUpVector();
    FVector forwardVector;

    if (loopTurn > 29)
        loopTurn = 25;

    int downSpeed[30]{ 
        4000000.0f, 4000000.0f, 4000000.0f, 4000000.0f, 800000.0f, 600000.0f, 500000.0f, 320000.0f, 320000.0f, 240000.0f,
        240000.0f, 120000.0f, 120000.0f, 400000.0f, 400000.0f, 100000.0f, 100000.0f, 40000.0f, 40000.0f, 40000.0f,
        40000.0f, 40000.0f, 40000.0f, 40000.0f, 40000.0f, 40000.0f, 40000.0f, 40000.0f, 40000.0f,  40000.0f,
    };

    const FVector relativeMoveVector = FVector(XMoveDirection*20, -YMoveDirection*20, 0);
    FVector worldMoveVector = GetActorRotation().RotateVector(relativeMoveVector);

    FVector force;
    if (CurrentState == APlayerFight_States::EPlayerFight_State::IdleJump || CurrentState == APlayerFight_States::EPlayerFight_State::Jump)
        force = ((upvector * -1) * downSpeed[loopTurn]) + (worldMoveVector * 1000);
    else
    {
        forwardVector = GetActorForwardVector();
        force = ((upvector * -1) * downSpeed[loopTurn]*2) + (forwardVector * downSpeed[loopTurn]*2) + (worldMoveVector * 1000);
    }

    PlayerController->GetCharacter()->GetCharacterMovement()->AddForce(force);
}


void APlayerFight_Actions::DebugBtnAction()
{
    UE_LOG(LogTemp, Warning, TEXT(" isStartJump = %s"), isStartJump ? TEXT("True") : TEXT("False")); 
    UE_LOG(LogTemp, Warning, TEXT(" isIdleJump = %s"), isIdleJump ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" isDashJump = %s"), isDashJump ? TEXT("True") : TEXT("False"));  
    UE_LOG(LogTemp, Warning, TEXT(" isDash = %s"), isDash ? TEXT("True") : TEXT("False"));  
    UE_LOG(LogTemp, Warning, TEXT(" isNearGround = %s"), isNearGround ? TEXT("True") : TEXT("False"));  
    UE_LOG(LogTemp, Warning, TEXT(" isSprint = %s"), isSprint ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" isSprintInput = %s"), isSprintInput ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" currentState = %d"), CurrentState ); 

}

void APlayerFight_Actions::RBBtnAction()
{
    UE_LOG(LogTemp, Warning, TEXT("DASH"));
    if (canDash == true && CurrentState != APlayerFight_States::EPlayerFight_State::DashJump)
    {
         canDash = false;
         isDash = true;
         loopTurn = 0;
         CancelGravity();
         SetCharacterState(APlayerFight_States::EPlayerFight_State::Dash, 0.0f);
         dashNumber++;
         if (dashNumber == 4)
             dashNumber = 1;
    }
}

void APlayerFight_Actions::DashAction()
{
    const FVector upvector = GetActorUpVector();
    FVector forwardVector = GetActorForwardVector();
    int currentspeed = 0;
    int upSpeed = 0;
    if (isNearGround)
    {
        int forSpeed[40]{
        40000000, 40000000, 40000000, 40000000, 8000000, 6000000, 5000000, 3200000, 3200000, 2400000,
        2400000, 1200000, 1200000, 4000000, 4000000, 1000000, 1000000, 400000, 400000, 400000,
        400000, 400000, 400000, 400000, 400000, 400000, 400000, 400000, 400000,  400000,
        400000, 400000, 400000, 400000, 400000, 400000, 400000, 400000, 400000,  400000,
        };
        currentspeed = forSpeed[loopTurn];
    }
    else
    {
        int forSpeed[40]{
        4000000, 4000000, 4000000, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, -100000, -100000, -100000, -100000, -200000, -300000, -400000, -1000000, -1500000,
        0, 0, 0, 0, 0, 0, 0, 0, 0,  0,
        };
        currentspeed = forSpeed[loopTurn];
        upSpeed = 100000;
    }
    const FVector relativeMoveVector = FVector(XMoveDirection * 20, -YMoveDirection * 20, 0);
    FVector worldMoveVector = GetActorRotation().RotateVector(relativeMoveVector);

    const FVector force = (upvector * upSpeed) + (forwardVector * currentspeed) + (worldMoveVector * 1000);

    PlayerController->GetCharacter()->GetCharacterMovement()->AddForce(force);
}

void APlayerFight_Actions::ActionTurn(bool canTurn)
{
    FVector Direction = FVector(XMoveDirection, -YMoveDirection, 0.0f);

    FRotator CamRotation = FollowCamera->GetComponentRotation();
    Direction = CamRotation.RotateVector(Direction);
    Direction.Z = 0.0f;

    FVector TargetLocation = GetActorLocation() + (Direction * (runSpeed * 500) * GetWorld()->DeltaTimeSeconds);

    FVector DirectionToTarget = TargetLocation - GetActorLocation();
    DirectionToTarget.Normalize();

    const FVector WorldUp(0.0f, 0.0f, 1.0f);

    FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

    FVector CurrentLocation = GetActorLocation();
    FRotator ActionTurnTargetRotations = (TargetLocation - CurrentLocation).Rotation();
 
    if (canTurn == true)
    {
        SetActorRotation(ActionTurnTargetRotations);
    }

}

//void APlayerFight_Actions::TakeDamage(int damage)
//{
//    UE_LOG(LogTemp, Warning, TEXT("TakeDamage"));
//}

bool APlayerFight_Actions::GetisStartJump()
{
    return isStartJump;
}
bool APlayerFight_Actions::GetisIdleJump()
{
    return isIdleJump;
}
bool APlayerFight_Actions::GetisDashJump()
{
    return isDashJump;
}
bool APlayerFight_Actions::GetisDash()
{
    return isDash;
}
int APlayerFight_Actions::GetdashNumber()
{
    return dashNumber;
}
void APlayerFight_Actions::CancelGravity()
{
    Super::CancelGravity();
}
void APlayerFight_Actions::ActivateGravity()
{
    Super::ActivateGravity();
}