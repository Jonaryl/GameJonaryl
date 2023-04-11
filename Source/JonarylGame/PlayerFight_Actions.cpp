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


    if (CurrentState != APlayerFight_States::EPlayerFight_State::DashJump  && CurrentState != APlayerFight_States::EPlayerFight_State::Dash)
        ActionTurn(false);

    if (CurrentState == APlayerFight_States::EPlayerFight_State::DashJump || CurrentState == APlayerFight_States::EPlayerFight_State::IdleJump || CurrentState == APlayerFight_States::EPlayerFight_State::Dash
        || CurrentState == APlayerFight_States::EPlayerFight_State::Idle && isNearGround == false
        || CurrentState == APlayerFight_States::EPlayerFight_State::Run && isNearGround == false)
    {
        /////////////////// raycast ///////////////////////////////////////////////////////// 

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

            if (DistanceToGround < oldDistanceToGround && DistanceToGround > 150)
            {
                isIdleJump = true;
            }
            
            if (DistanceToGround < 150)
            {
                isNearGround = true;
                isDashJump = false;
            }
        }
        /////////////////// raycast ///////////////////////////////////////////////////////// 
    }

    if (CurrentState == APlayerFight_States::EPlayerFight_State::Jump || CurrentState == APlayerFight_States::EPlayerFight_State::DashJump
        || CurrentState == APlayerFight_States::EPlayerFight_State::Dash)
    {
        int sens = 1;
        if (CurrentState == APlayerFight_States::EPlayerFight_State::DashJump)
        {
            sens = -1;
            forwardSpeed = 500000;
        }
        const FVector upvector = GetActorUpVector() * sens;
        FVector forwardVector;
        if (forwardSpeed != 0)
        {
            forwardVector = GetActorForwardVector();
        }
        else
        {
            forwardVector = FVector(0,0,0);
        }
        const FVector relativeMoveVector = FVector(XMoveDirection*20, -YMoveDirection*20, 0);
        FVector worldMoveVector = GetActorRotation().RotateVector(relativeMoveVector);

        const FVector force = (upvector * jumpSpeed) + (forwardVector * forwardSpeed) + (worldMoveVector * 1000);

        PlayerController->GetCharacter()->GetCharacterMovement()->AddForce(force);
        // Contrôler la vitesse du dash
        if (CurrentState == APlayerFight_States::EPlayerFight_State::Dash)
        {
            if (loopTurn < 4)
                ActionTurn(true);
            if (isNearGround)
            {
                if (forwardSpeed > 50000000.0f)
                    forwardSpeed = 5000000.0f;
                else if (forwardSpeed > 0.0f)
                    forwardSpeed -= 5000000.0f * GetWorld()->GetDeltaSeconds();
                else
                {
                    SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle, 0.0f);
                    isDash = false;
                    canDash = true;
                    forwardSpeed = 0;
                }
            }
            else
            {
                if (forwardSpeed > 5000000.0f)
                    forwardSpeed = 100000.0f;
                else if (forwardSpeed > 0.0f)
                {
                    forwardSpeed -= 2000000.0f * GetWorld()->GetDeltaSeconds();
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT(" bIsGrounded = %s"), bIsGrounded ? TEXT("True") : TEXT("False"));
                    if(bIsGrounded)
                        SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle, 0.0f);
                    else
                    {
                        SetCharacterState(APlayerFight_States::EPlayerFight_State::IdleJump, 0.0f);
                        UE_LOG(LogTemp, Warning, TEXT(" 01 IdleJump"));
                    }
                    isDash = false;
                    canDash = true;
                    forwardSpeed = 0;
                }
            }
            loopTurn++;
        }
        else
        {
            if (jumpSpeed > 2000000.0f && CurrentState != APlayerFight_States::EPlayerFight_State::DashJump)
            {
                jumpSpeed = 50000.0f;
                if (forwardSpeed != 0)
                    forwardSpeed = 90000.0f;
            }
            else if (loopTurn < 4 && CurrentState == APlayerFight_States::EPlayerFight_State::DashJump && FMath::Abs(XMoveDirection) + FMath::Abs(YMoveDirection) != 0.0f)
            {
                loopTurn++;
                ActionTurn(true);

            }
            else if (jumpSpeed > 0.0f) 
            {
                jumpSpeed -= 50000.0f * GetWorld()->GetDeltaSeconds();
                if (forwardSpeed != 0 && CurrentState != APlayerFight_States::EPlayerFight_State::DashJump)
                    forwardSpeed -= 50000.0f * GetWorld()->GetDeltaSeconds();
                //else if (CurrentState == APlayerFight_States::EPlayerFight_State::DashJump)
                //    forwardSpeed -= 5000.0f * GetWorld()->GetDeltaSeconds();
            }
            else {
                jumpSpeed = 0.0f;

                if (isStartJump == true )
                {
                    isStartJump = false;
                    SetCharacterState(APlayerFight_States::EPlayerFight_State::IdleJump, 0.8f);
                    UE_LOG(LogTemp, Warning, TEXT(" 02 IdleJump"));
                }
            }
        }
    }
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
        //UE_LOG(LogTemp, Warning, TEXT(" Jump action = %d"), CurrentState);
        jumpSpeed = 2400000.0f;
        //jumpSpeed = 3700000.0f;
        //jumpSpeed = 5400000.0f;
        if (FMath::Abs(XMoveDirection) + FMath::Abs(YMoveDirection) > 0.0f)
        {
            forwardSpeed = 180000.0f;
        }
        else
        {
            forwardSpeed = 0.0f;
        }

        if (PlayerController->GetCharacter() && PlayerController->GetCharacter()->GetCharacterMovement()) 
        {
            //UE_LOG(LogTemp, Warning, TEXT(" Jump PlayerController = %d"), CurrentState);
            XMoveDirection = 0.0f;
            YMoveDirection = 0.0f;
            //UE_LOG(LogTemp, Error, TEXT("Jump"));
            SetCharacterState(APlayerFight_States::EPlayerFight_State::Jump, 0.0f);
            UE_LOG(LogTemp, Warning, TEXT("Jump "));
            isStartJump = true;
            isNearGround = false;
        }
        else {
            UE_LOG(LogTemp, Error, TEXT("PlayerMesh is null"));
        }
    }
    else if (CurrentState == APlayerFight_States::EPlayerFight_State::IdleJump || CurrentState == APlayerFight_States::EPlayerFight_State::Jump)
    {
        if (isNearGround == false)
        {
            //UE_LOG(LogTemp, Warning, TEXT(" CurrentState IdleJump = %d"), CurrentState);
            jumpSpeed = 3600000.0f;
 
            forwardSpeed = 0.0f;

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


void APlayerFight_Actions::BBtnAction()
{
    UE_LOG(LogTemp, Warning, TEXT(" isStartJump = %s"), isStartJump ? TEXT("True") : TEXT("False")); 
    UE_LOG(LogTemp, Warning, TEXT(" isIdleJump = %s"), isIdleJump ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" isDashJump = %s"), isDashJump ? TEXT("True") : TEXT("False"));  
    UE_LOG(LogTemp, Warning, TEXT(" isDash = %s"), isDash ? TEXT("True") : TEXT("False"));  
    UE_LOG(LogTemp, Warning, TEXT(" isNearGround = %s"), isNearGround ? TEXT("True") : TEXT("False"));  
    UE_LOG(LogTemp, Warning, TEXT(" currentState = %d"), CurrentState ); 

}

void APlayerFight_Actions::RBBtnAction()
{
    UE_LOG(LogTemp, Warning, TEXT("DASH"));
    if (canDash == true && CurrentState != APlayerFight_States::EPlayerFight_State::DashJump)
    {
         canDash = false;
         isDash = true;
         jumpSpeed = 0.0f;
         //UE_LOG(LogTemp, Warning, TEXT(" isNearGround = %s"), isNearGround ? TEXT("True") : TEXT("False"));
         if(isNearGround)
            forwardSpeed = 60000000.0f;
         else
            forwardSpeed = 660000.0f;
         //UE_LOG(LogTemp, Warning, TEXT(" forwardSpeed = %f"), forwardSpeed);
         loopTurn = 0;
         CancelGravity();
         SetCharacterState(APlayerFight_States::EPlayerFight_State::Dash, 0.0f);
    }
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
void APlayerFight_Actions::CancelGravity()
{
    Super::CancelGravity();
}
void APlayerFight_Actions::ActivateGravity()
{
    Super::ActivateGravity();
}