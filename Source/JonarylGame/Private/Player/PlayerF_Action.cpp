// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerF_Action.h"

void APlayerF_Action::BeginPlay()
{
    Super::BeginPlay();
    PrimaryActorTick.bCanEverTick = true;

}

void APlayerF_Action::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    GroundRaycast();
    //// JUMP UP
    if (CurrentState == AStates_PlayerF::EStates_PlayerF::JumpUp)
    {
        actionJumpTurn++;
        if (actionJumpTurn >= 0)
            ActionJumpUp();

        if (actionJumpTurn == JumpUpMaxTurn)
        {
            UE_LOG(LogTemp, Error, TEXT(" JUMP UP END "));
            SetCharacterState(AStates_PlayerF::EStates_PlayerF::IdleJump, 0.0f);
            actionJumpTurn = 0;

            isJumpIdle = true;
            isJumpUp = false;
        }
    }
    //// JUMP iDLE
    if (CurrentState == AStates_PlayerF::EStates_PlayerF::IdleJump)
    {
        actionJumpTurn++;
        if (actionJumpTurn >= 0)
            ActionJumpIdle();

        if (isGrounded)
        {
            UE_LOG(LogTemp, Error, TEXT(" IdleJump END "));
            EndJump();
        }
        if (actionJumpTurn == JumpIdleMaxTurn)
        {
            UE_LOG(LogTemp, Error, TEXT(" JUMP IDLE END "));
            SetCharacterState(AStates_PlayerF::EStates_PlayerF::JumpDown, 0.0f);
            actionJumpTurn = 0;
            CancelGravity();

            isJumpDown = true;
            isJumpIdle = false;
        }
    }
    //// JUMP DOWN
    if (CurrentState == AStates_PlayerF::EStates_PlayerF::JumpDown)
    {
        actionJumpTurn++;
        if (actionJumpTurn >= 0)
            ActionJumpDown();

        if (actionJumpTurn == JumpDownMaxTurn || isGrounded)
        {
            UE_LOG(LogTemp, Error, TEXT(" JUMP DOWN END "));
            EndJump();
        }
    }
    //// JUMP DASH
    if (CurrentState == AStates_PlayerF::EStates_PlayerF::DashJump)
    {
        actionJumpTurn++;
        if (actionJumpTurn >= 0)
            ActionJumpDash();

        if (actionJumpTurn == JumpDashMaxTurn || isGrounded)
        {
            UE_LOG(LogTemp, Error, TEXT(" JUMP DASH END "));
            EndJump();
        }
    }
    //// DASH
    if (CurrentState == AStates_PlayerF::EStates_PlayerF::Dash)
    {
        actionDashTurn++;
        if (actionDashTurn >= 0)
            ActionDash();

        if (actionDashTurn == dashMaxTurn)
        {
            UE_LOG(LogTemp, Error, TEXT(" DASH END "));
            EndDash();
            CancelGravity();
        }
    }
}

void APlayerF_Action::NeutralAction() {}
void APlayerF_Action::EndAllActionAnim()
{
    Super::EndAllActionAnim();
    DisableFriction(1.0f);
}

///////////////////////////////////////////////////////////////
//////////////////////////// JUMP /////////////////////////////
//// JUMP UP
void APlayerF_Action::ActionJumpUp()
{
    int speed[30]{
        900.0f, 450.0f, 220.0f, 160.0f,
        90.0f, 70.0f, 50.0f, 35.0f, 18.0f, 16.0f, 11.0f, 8.0f, 5.0f, 
        3.0f, 1.0f, 0.80f, 0.50f, 0.30f, 0.150f, 0.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,-10.0f,-10.0f,
        0.0f
    };
    AddForce(1, speed[actionJumpTurn], 1);
}
//// JUMP IDLE
void APlayerF_Action::ActionJumpIdle()
{
    int speed[30]{
        4.0f, 3.0f, 0.8f, 0.6f,
        0.2f, 0.08f, 0.04f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f,
        0.0f
    };

    AddForce(1, speed[actionJumpTurn], 1);
}
//// JUMP DOWN
void APlayerF_Action::ActionJumpDown()
{
    int speed[21]{
        0.1f, 0.5f, 1.0f, 2.0f, 5.0f, 10.0f, 20.0f,
        40.0f, 60.0f, 80.0f, 100.0f,
        200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 200.0f,
        200.0f
    };
    AddForce(-1, speed[actionJumpTurn], 1);
}
//// JUMP DASH
void APlayerF_Action::ActionJumpDash()
{
    int speed[30]{
        800.0f, 600.0f, 400.0f, 200.0f,
        100.0f, 80.0f, 40.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f,
        0.0f
    };
    AddForce(-1, speed[actionJumpTurn], JumpDashForwardSpeed);
}
//// JUMP END
void APlayerF_Action::EndJump()
{
    EndAllActionAnim();

    if(isMoveInput)
        SetCharacterState(AStates_PlayerF::EStates_PlayerF::Run, 0.0f);
    else
        SetCharacterState(AStates_PlayerF::EStates_PlayerF::Idle, 0.0f);

    NeutralAction();
    CancelGravity();
}
//////////////////////////// JUMP /////////////////////////////
///////////////////////////////////////////////////////////////
 
///////////////////////////////////////////////////////////////
//////////////////////////// DASH /////////////////////////////
//// DASH
void APlayerF_Action::ActionDash()
{
    int speed[40]{
        15000, 2000, 800, 400, 270, 230, 250, 100, 100, 80,
        80, 43, 43, 35, 35, 27, 27, 15, 15, 15,
        15, 15, 15, 15, 15, 15, 15, 15, 15,  15,
        15, 15, 15, 15, 15, 15, 15, 15, 15,  15,
    };
    AddForce(1, 0, (speed[actionDashTurn] * dashForce));
}
//// DASH END
void APlayerF_Action::EndDash()
{
    DisableFriction(1.0f);
    isDash = false;

    if (!isGrounded)
    {
        actionJumpTurn = 5;

        isJumpIdle = true;

        SetCharacterState(AStates_PlayerF::EStates_PlayerF::IdleJump, 0.0f);
    }
    else
    {
        if(isMoveInput)
            SetCharacterState(AStates_PlayerF::EStates_PlayerF::Run, 0.0f);
        else
            SetCharacterState(AStates_PlayerF::EStates_PlayerF::Idle, 0.0f);
        canBeHit = true;
        canSprint = true;

        NeutralAction();
    }
    SetActorLocation(
        FMath::VInterpTo(GetActorLocation(), GetActorLocation(), GetWorld()->DeltaTimeSeconds, 1.0f)
    );
    CancelGravity();
}


//////////////////////////// DASH /////////////////////////////
///////////////////////////////////////////////////////////////

//////////////////////////// ADD FORCE /////////////////////////////
void APlayerF_Action::AddForce(int sens, int speedV, int speedH)
{
    const FVector UpVector = GetActorUpVector();
    const FVector RightVector = GetActorRightVector();
    const FVector ForwardVector = GetActorForwardVector();


    ///CALCUL FORCE UP DOWN
    FVector UpForce; 
    if (CurrentState == AStates_PlayerF::EStates_PlayerF::Dash)
        UpForce = FVector(0,0,0);
    else if (CurrentState == AStates_PlayerF::EStates_PlayerF::JumpDown && isNearGround 
        || CurrentState == AStates_PlayerF::EStates_PlayerF::DashJump && isNearGround)
    {
        UpForce = (UpVector * speedV * sens) * (JumpForce / 10);
    }
    else
        UpForce = (UpVector * speedV * sens) * JumpForce;
    ////////////////////////////
    
    ///CALCUL FORCE BACK FORWARD RIGHT LEFT    
    FVector XYForce;
    if (speedH == 1)
        XYForce = ForwardVector * (FMath::Abs(MoveValue.XValue) + FMath::Abs(MoveValue.YValue)) * JumpMoveSpeed;
    else if (CurrentState == AStates_PlayerF::EStates_PlayerF::Dash)
        XYForce = ForwardVector * speedH + (FMath::Abs(MoveValue.XValue) + FMath::Abs(MoveValue.YValue));
    else
        XYForce = ForwardVector * speedH;
    ////////////////////////////

    //const FVector AppliedForce = GetActorLocation() + (UpForce + XYForce) * GetWorld()->DeltaTimeSeconds;
    const FVector AppliedForce = GetActorLocation() + ((UpForce * GetWorld()->DeltaTimeSeconds) + XYForce);

    /*
    UE_LOG(LogTemp, Warning, TEXT(" isMoveInput = %s"), isMoveInput ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" XYForce = %s"), *XYForce.ToString());
    UE_LOG(LogTemp, Warning, TEXT(" AppliedForce = %s"), *AppliedForce.ToString());
    */
    if (isMoveInput)
    {
        ActionMovingAndTurning(AppliedForce, actionJumpTurn, 5000000000.0f, 2.0f);
    }
    else
        ActionMovingAndTurning(AppliedForce, actionJumpTurn, 0, 0);

        /*
    SetActorLocation(
        FMath::VInterpTo(GetActorLocation(), AppliedForce, GetWorld()->DeltaTimeSeconds, 100.0f)
    );
    //GetCharacterMovement()->AddForce(AppliedForce);
        */
}

//////////////////////////// INPUT /////////////////////////////
void APlayerF_Action::ABtnAction()
{
    if (CurrentState != AStates_PlayerF::EStates_PlayerF::JumpDown
        && CurrentState != AStates_PlayerF::EStates_PlayerF::JumpUp
        && CurrentState != AStates_PlayerF::EStates_PlayerF::IdleJump)
    {
        EndAllActionAnim();
        actionJumpTurn = 0;
        SetCharacterState(AStates_PlayerF::EStates_PlayerF::JumpUp, 0.0f);

        isJumpUp = true;
    }
    else if (CurrentState == AStates_PlayerF::EStates_PlayerF::JumpDown
        || CurrentState == AStates_PlayerF::EStates_PlayerF::JumpUp
        || CurrentState == AStates_PlayerF::EStates_PlayerF::Dash && isGrounded == false
        || CurrentState == AStates_PlayerF::EStates_PlayerF::IdleJump)
    {
        EndAllActionAnim();
        actionJumpTurn = 0;
        SetCharacterState(AStates_PlayerF::EStates_PlayerF::DashJump, 0.0f);

        isJumpDash = true;
    }
}
void APlayerF_Action::RBBtnAction()
{
    if (CurrentState != AStates_PlayerF::EStates_PlayerF::Dash 
        && CurrentState != AStates_PlayerF::EStates_PlayerF::DashJump
        && CurrentState != AStates_PlayerF::EStates_PlayerF::JumpDown
        && CurrentState != AStates_PlayerF::EStates_PlayerF::JumpUp
        && CurrentState != AStates_PlayerF::EStates_PlayerF::IdleJump
        )
    {
        StopRootMotion();
        EndAllActionAnim();
        DisableFriction(0.0f);

        if(!isGrounded)
            CancelGravity();

        actionDashTurn = 0;

        canBeHit = false;
        canSprint = false;

        isDash = true;
        dashNumber++;
        if (dashNumber == 4)
            dashNumber = 1;

        SetCharacterState(AStates_PlayerF::EStates_PlayerF::Dash, 0.0f);
    }
}
void APlayerF_Action::DebugBtnAction()
{
    Super::DebugBtnAction();
    UE_LOG(LogTemp, Error, TEXT(" ACTION "));

    UE_LOG(LogTemp, Warning, TEXT(" isDash = %s"), isDash ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" isGrounded = %s"), isGrounded ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" isJumpUp = %s"), isJumpUp ? TEXT("True") : TEXT("False")); 
    UE_LOG(LogTemp, Warning, TEXT(" isJumpIdle = %s"), isJumpIdle ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" isJumpDown = %s"), isJumpDown ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" isJumpDash = %s"), isJumpDash ? TEXT("True") : TEXT("False"));
}

//////////////////////////// RAYCAST /////////////////////////////
void APlayerF_Action::GroundRaycast()
{
    float GroundCheckDistance = 6000.0f;
    FVector StartLocation = GetActorLocation();
    FVector EndLocation = StartLocation - FVector(0.0f, 0.0f, GroundCheckDistance);
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 0.1f, 0, 2.0f);
    bool bIsGrounded = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams);

    if (bIsGrounded)
    {
        float oldDistanceToGround = distanceToGround;
        distanceToGround = HitResult.Distance;
        //UE_LOG(LogTemp, Log, TEXT(" distanceToGround = %f"), distanceToGround);

        if (distanceToGround < 150)
            isNearGround = true;
        else
            isNearGround = false;

        if (distanceToGround < distanceToBeGrounded)
            isGrounded = true;
        else
            isGrounded = false;
    }
}


//////////////////////////// GRAVITY /////////////////////////////
void APlayerF_Action::CancelGravity()
{
    PlayerController->GetCharacter()->GetCharacterMovement()->StopMovementImmediately();
    PlayerController->GetCharacter()->GetCharacterMovement()->Velocity = FVector::ZeroVector;
}
void APlayerF_Action::ActivateGravity()
{
    GetCharacterMovement()->GravityScale = 1.0f;
}
void APlayerF_Action::DisableFriction(float friction)
{
    if (PlayerController)
    {
        ACharacter* Character = Cast<ACharacter>(PlayerController->GetCharacter());
        if (Character)
        {
            UCharacterMovementComponent* CharacterMove = Character->GetCharacterMovement();
            if (CharacterMove)
            {
                CharacterMove->GroundFriction = friction;
            }
        }
    }
}
void APlayerF_Action::StopRootMotion()
{
    if (PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT(" layerController "));
        ACharacter* Character = Cast<ACharacter>(PlayerController->GetCharacter());
        if (Character)
        {
            UE_LOG(LogTemp, Warning, TEXT(" Character "));
            Character->LaunchCharacter(FVector(0, 0, 0), false, false);
        }
    }
}

/////////////////////////// DAMAGE ///////////////////////////
void APlayerF_Action::DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, int damageCut, AActor* Enemy){}
