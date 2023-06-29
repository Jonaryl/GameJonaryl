// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Move.h"
#include "GameplayTagContainer.h"
#include "Input/Events.h"

#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"


APlayerFight_Move::APlayerFight_Move()
{
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    MyMeshTest = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));

    FVector SpawnLocation = FVector(0.0f, 0.0f, 1.0f);
    FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
    SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
}

void APlayerFight_Move::BeginPlay()
{
    Super::BeginPlay();

    PlayerController = Cast<APlayerController>(GetController());
    PlayerMesh = Cast<UPrimitiveComponent>(PlayerController->GetCharacter()->GetMesh());
    //PlayerMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    //PlayerMesh = PlayerController->GetComponentByClass(UStaticMeshComponent::StaticClass());

    if (PlayerController)
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        if (Subsystem)
        {
            Subsystem->AddMappingContext(PlayerMappingContext, 0);
        }
    }
}

void APlayerFight_Move::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInputComponent)
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerFight_Move::MoveForward);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &APlayerFight_Move::StartMoving); 
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerFight_Move::StopMoving); 

        EnhancedInputComponent->BindAction(MoveCamera, ETriggerEvent::Triggered, this, &APlayerFight_Move::TurnCamera);

        EnhancedInputComponent->BindAction(ABtn, ETriggerEvent::Triggered, this, &APlayerFight_Move::ABtnAction);
        EnhancedInputComponent->BindAction(BBtn, ETriggerEvent::Triggered, this, &APlayerFight_Move::BBtnAction);
        EnhancedInputComponent->BindAction(XBtn, ETriggerEvent::Triggered, this, &APlayerFight_Move::XBtnAction);
        EnhancedInputComponent->BindAction(YBtn, ETriggerEvent::Triggered, this, &APlayerFight_Move::YBtnAction);

        EnhancedInputComponent->BindAction(RBBtn, ETriggerEvent::Triggered, this, &APlayerFight_Move::RBBtnAction);  
        EnhancedInputComponent->BindAction(RBBtnHold, ETriggerEvent::Ongoing, this, &APlayerFight_Move::RBBtnActionHold); 
        EnhancedInputComponent->BindAction(RBBtnEnd, ETriggerEvent::Triggered, this, &APlayerFight_Move::RBBtnActionEnd); 


        EnhancedInputComponent->BindAction(DebugBtn, ETriggerEvent::Triggered, this, &APlayerFight_Move::DebugBtnAction);
    }

}

void APlayerFight_Move::StartMoving()
{
    if (CurrentState != APlayerFight_States::EPlayerFight_State::Jump && CurrentState != APlayerFight_States::EPlayerFight_State::IdleJump &&
        CurrentState != APlayerFight_States::EPlayerFight_State::Attack && CurrentState != APlayerFight_States::EPlayerFight_State::Counter &&
        CurrentState != APlayerFight_States::EPlayerFight_State::CounterAttack && CurrentState != APlayerFight_States::EPlayerFight_State::CounterPose &&
        CurrentState != APlayerFight_States::EPlayerFight_State::DashJump && CurrentState != APlayerFight_States::EPlayerFight_State::Dash)
    {
        SetCharacterState(APlayerFight_States::EPlayerFight_State::Run, 0.0f);
        //UE_LOG(LogTemp, Warning, TEXT("StartMoving %d"), CurrentState);
    }
}
void APlayerFight_Move::StopMoving()
{
    isMoveInput = false;
    if (CurrentState == APlayerFight_States::EPlayerFight_State::Run)
    {
        SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle, 0.0f);
        //UE_LOG(LogTemp, Warning, TEXT("StopMoving %d"), CurrentState);
    }
}

void APlayerFight_Move::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (valueSpeed > 0.f)
    {
        if (isMoveInput == false)
        {
            float ReduceFactor = ((valueSpeed - (0.1f + InitialSpeed)) * -1);
            valueSpeed -= (valueSpeed * ReduceFactor) * GetWorld()->DeltaTimeSeconds;
            valueSpeed = FMath::Max(valueSpeed, 0.f);

            //UE_LOG(LogTemp, Warning, TEXT("CurrentSpeed pressed with value %f"), valueSpeed);

            FVector Direction = GetActorForwardVector();
            FVector NewLocation = GetActorLocation() + Direction * valueSpeed * DeltaTime;
            SetActorLocation(NewLocation);
            XMoveDirection = 0.0f;
            YMoveDirection = 0.0f;
        }
    }

}

void APlayerFight_Move::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);
    UE_LOG(LogTemp, Warning, TEXT("Landed %d"), CurrentState);
    if(isMoveInput == true)
        SetCharacterState(APlayerFight_States::EPlayerFight_State::Run, 0.30f);
    else
        SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle, 0.30f);
    UE_LOG(LogTemp, Warning, TEXT("Landed après %d"), CurrentState);
    isStartJump = false;
    isIdleJump = false;
    isDashJump = false;
    isDash = false;
    canDash = true;
    //UE_LOG(LogTemp, Warning, TEXT("Landed"));
    // Votre code ici pour détecter que le personnage touche le sol
}


void APlayerFight_Move::MoveForward(const FInputActionValue& Value)
{
    FVector2D CurrentValue = Value.Get<FVector2D>();
    const float XValue = CurrentValue.X;
    const float YValue = CurrentValue.Y * -1;
    XMoveDirection = XValue;
    YMoveDirection = YValue;

    if (CurrentState != APlayerFight_States::EPlayerFight_State::Attack && CurrentState != APlayerFight_States::EPlayerFight_State::Counter &&
        CurrentState != APlayerFight_States::EPlayerFight_State::CounterAttack && CurrentState != APlayerFight_States::EPlayerFight_State::CounterPose &&
        CurrentState != APlayerFight_States::EPlayerFight_State::DashJump && CurrentState != APlayerFight_States::EPlayerFight_State::Dash)
    {
        isMoveInput = true;
        if (CurrentState == APlayerFight_States::EPlayerFight_State::Idle)
            SetCharacterState(APlayerFight_States::EPlayerFight_State::Run, 0.0f);

        if (CurrentValue.IsNearlyZero()) 
        {
            valueSpeed = FMath::FInterpTo(valueSpeed, 0.f, GetWorld()->DeltaTimeSeconds, 10.0f);
        }
        else
        {
            valueSpeed += (100.2f * GetWorld()->DeltaTimeSeconds);
            valueSpeed = FMath::Clamp(valueSpeed, 0.f, maxRunSpeed);
        }
        InitialSpeed = valueSpeed;
        valueSpeedJoy = YValue + XValue;

        if (Controller && valueSpeed != 0.0f)
        {
            bEnableInterpolation = true;
            if (bEnableInterpolation)
            {
                FVector Direction = FVector(XValue, -YValue, 0.0f); 

                FRotator CamRotation = FollowCamera->GetComponentRotation();
                Direction = CamRotation.RotateVector(Direction);
                Direction.Z = 0.0f;

                float sprintSpeed = 1.0;
                if (CurrentState == APlayerFight_States::EPlayerFight_State::Sprint)
                {
                    isSprint = true;
                    sprintSpeed = 2.0f;
                }

                FVector TargetLocation;
                if (CurrentState == APlayerFight_States::EPlayerFight_State::Sprint || CurrentState == APlayerFight_States::EPlayerFight_State::Run ||
                    CurrentState == APlayerFight_States::EPlayerFight_State::Idle || CurrentState == APlayerFight_States::EPlayerFight_State::DashJump)
                    TargetLocation = GetActorLocation() + (Direction * ((runSpeed * sprintSpeed) * valueSpeed) * GetWorld()->DeltaTimeSeconds);
                else
                    TargetLocation = GetActorLocation() + (Direction * ((runSpeed /1.5) * valueSpeed) * GetWorld()->DeltaTimeSeconds);


                FVector DirectionToTarget = TargetLocation - GetActorLocation();
                DirectionToTarget.Normalize();

                const FVector WorldUp(0.0f, 0.0f, 1.0f);

                FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

                FQuat InterpolatedRotation;
                if (CurrentState == APlayerFight_States::EPlayerFight_State::Sprint || CurrentState == APlayerFight_States::EPlayerFight_State::Run ||
                    CurrentState == APlayerFight_States::EPlayerFight_State::Idle || CurrentState == APlayerFight_States::EPlayerFight_State::DashJump)
                    InterpolatedRotation = FQuat::Slerp(GetActorRotation().Quaternion(), lookAtRotation.Quaternion(), GetWorld()->DeltaTimeSeconds * runRotationSpeed);
                else
                    InterpolatedRotation = FQuat::Slerp(GetActorRotation().Quaternion(), lookAtRotation.Quaternion(), GetWorld()->DeltaTimeSeconds * runRotationSpeed/10);

                SetActorRotation(InterpolatedRotation.Rotator());

                MyMeshTest->SetRelativeLocation(TargetLocation);

                SetActorLocationAndRotation(
                    FMath::VInterpTo(GetActorLocation(), TargetLocation, GetWorld()->DeltaTimeSeconds, 100.0f),
                    FMath::RInterpTo(GetActorRotation(), InterpolatedRotation.Rotator(), GetWorld()->DeltaTimeSeconds, 100.0f)       
                );
            }
            else
            {
                AddMovementInput(FVector(1.0f, 0.0f, 0.0f), valueSpeedJoy);
            }
        }
    }
}

void APlayerFight_Move::TurnCamera(const FInputActionValue& Value)
{
    const FVector2D CurrentValue = Value.Get<FVector2D>();

    PlayerController->AddYawInput(CurrentValue.X * 40.0f * GetWorld()->GetDeltaSeconds());
    PlayerController->AddPitchInput(CurrentValue.Y * 40.0f * GetWorld()->GetDeltaSeconds());
}

void APlayerFight_Move::ChangeCharacterState(APlayerFight_States::EPlayerFight_State NewState)
{
    //UE_LOG(LogTemp, Warning, TEXT("02 avant CurrentState = %d"), CurrentState);
    //APlayerFight_States::EPlayerFight_State NewState = static_cast<APlayerFight_States::EPlayerFight_State>(reinterpret_cast<uintptr_t>(NewStatePtr));
    CurrentState = NewState;
    UE_LOG(LogTemp, Warning, TEXT("03 change d'etat CurrentState = %d"), CurrentState);
}


void APlayerFight_Move::SetCharacterState(APlayerFight_States::EPlayerFight_State NewState, float Time)
{
    FTimerHandle TimerHandle;
    FTimerDelegate TimerDel;
    //UE_LOG(LogTemp, Error, TEXT("01 NewState = %d"), NewState); 
    TimerDel.BindUObject(this, &APlayerFight_Move::ChangeCharacterState, NewState);
    if (Time == 0.0f)
        APlayerFight_Move::ChangeCharacterState(NewState);
    else
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, Time, false);
    //GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerFight_Move::ChangeCharacterState, Time, false, 0.0f, (void*)NewState);

}

void APlayerFight_Move::CancelGravity()
{   
    //const FVector upvector = GetActorUpVector();
   // const FVector force = (upvector * 200000.0f);
    //PlayerController->GetCharacter()->GetCharacterMovement()->AddForce(force); 
    //GetCharacterMovement()->GravityScale = 0.f;
    PlayerController->GetCharacter()->GetCharacterMovement()->StopMovementImmediately();
    PlayerController->GetCharacter()->GetCharacterMovement()->Velocity = FVector::ZeroVector;
}
void APlayerFight_Move::ActivateGravity() 
{   
    GetCharacterMovement()->GravityScale = 1.0f; 
}


void APlayerFight_Move::ABtnAction(){}
void APlayerFight_Move::BBtnAction(){}
void APlayerFight_Move::XBtnAction(){}
void APlayerFight_Move::YBtnAction(){}

void APlayerFight_Move::RBBtnAction(){}
void APlayerFight_Move::DebugBtnAction(){}


void APlayerFight_Move::RBBtnActionHold()
{
    isSprintInput = true;
    if (isMoveInput == true && CurrentState == APlayerFight_States::EPlayerFight_State::Run ||
        isMoveInput == true && CurrentState == APlayerFight_States::EPlayerFight_State::Sprint)
    {
        SetCharacterState(APlayerFight_States::EPlayerFight_State::Sprint, 0.0f);
        isSprint = true;
    }
}

void APlayerFight_Move::RBBtnActionEnd()
{
    isSprintInput = false;
    if (isMoveInput == true && CurrentState == APlayerFight_States::EPlayerFight_State::Run ||
        isMoveInput == true && CurrentState == APlayerFight_States::EPlayerFight_State::Sprint)
    {
        SetCharacterState(APlayerFight_States::EPlayerFight_State::Run, 0.0f);
    }
    isSprint = false;
}




float APlayerFight_Move::GetSpeed()
{
    return valueSpeed;
}
bool APlayerFight_Move::GetisIdle()
{
    return isIdle;
}
bool APlayerFight_Move::GetisSprint()
{
    return isSprint;
}
bool APlayerFight_Move::GetisNearGround()
{
    return isNearGround;
}



