﻿// Fill out your copyright notice in the Description page of Project Settings.


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
    }

}

void APlayerFight_Move::StartMoving()
{
    if (CurrentState != APlayerFight_States::EPlayerFight_State::Jump && CurrentState != APlayerFight_States::EPlayerFight_State::IdleJump 
        && CurrentState != APlayerFight_States::EPlayerFight_State::DashJump)
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
    SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle, 0.30f);
    UE_LOG(LogTemp, Warning, TEXT("Landed après %d"), CurrentState);
    isStartJump = false;
    isIdleJump = false;
    isDashJump = false;
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

    if (CurrentState != APlayerFight_States::EPlayerFight_State::Jump && CurrentState != APlayerFight_States::EPlayerFight_State::IdleJump &&
        CurrentState != APlayerFight_States::EPlayerFight_State::DashJump)
    {
        isMoveInput = true;

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

                FVector TargetLocation = GetActorLocation() + (Direction * (runSpeed * valueSpeed) * GetWorld()->DeltaTimeSeconds);

                FVector DirectionToTarget = TargetLocation - GetActorLocation();
                DirectionToTarget.Normalize();

                const FVector WorldUp(0.0f, 0.0f, 1.0f);

                FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

                FQuat InterpolatedRotation = FQuat::Slerp(GetActorRotation().Quaternion(), lookAtRotation.Quaternion(), GetWorld()->DeltaTimeSeconds * runRotationSpeed);
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
    //UE_LOG(LogTemp, Warning, TEXT("03 change d'etat CurrentState = %d"), CurrentState);
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

//void APlayerFight_Move::BButton() {} 
//void APlayerFight_Move::XButton() {}
//void APlayerFight_Move::YButton() {}

void APlayerFight_Move::ABtnAction(){}
void APlayerFight_Move::BBtnAction(){}




float APlayerFight_Move::GetSpeed()
{
    return valueSpeed;
}
bool APlayerFight_Move::GetisIdle()
{
    return isIdle;
}
bool APlayerFight_Move::GetisNearGround()
{
    return isNearGround;
}

