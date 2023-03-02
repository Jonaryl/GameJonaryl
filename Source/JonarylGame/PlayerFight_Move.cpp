// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Move.h"
#include "GameplayTagContainer.h"
#include "Input/Events.h"

#include "Math/UnrealMathUtility.h"


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
}

void APlayerFight_Move::BeginPlay()
{
    Super::BeginPlay();

    PlayerController = Cast<APlayerController>(GetController());
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
        EnhancedInputComponent->BindAction(MoveCamera, ETriggerEvent::Triggered, this, &APlayerFight_Move::TurnCamera);
    }
}

void APlayerFight_Move::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (valueSpeed > 0.f)
    {
        FInputActionValue ActionValue = EnhancedInputComponent->GetBoundActionValue(MoveAction);

        float AxisValueX, AxisValueY;
        PlayerController->GetInputAnalogStickState(EControllerAnalogStick::CAS_LeftStick, AxisValueX, AxisValueY);

        float AxisValue = AxisValueX + AxisValueY;

        UE_LOG(LogTemp, Warning, TEXT("Le joueur appuie sur le stick gauche value %f"), AxisValue);
        UE_LOG(LogTemp, Warning, TEXT("valueSpeed %f"), valueSpeed);
        if (FMath::Abs(AxisValue) < 0.0f)
        {
            if (FMath::Abs(AxisValue) > 0.f)
            {
                // Si la touche de déplacement n'est pas utilisée, on diminue la vitesse de déplacement
                valueSpeed -= 300.0f * GetWorld()->DeltaTimeSeconds;
                valueSpeed = FMath::Max(valueSpeed, 0.f);
                UE_LOG(LogTemp, Warning, TEXT("CurrentSpeed pressed with value %f"), valueSpeed);
            }
        }

    }

}

void APlayerFight_Move::MoveForward(const FInputActionValue& Value)
{
    FVector2D CurrentValue = Value.Get<FVector2D>();
    const float XValue = CurrentValue.X;
    const float YValue = CurrentValue.Y * -1;

    if (CurrentValue.IsNearlyZero()) // Si l'utilisateur ne presse aucune touche de mouvement
    {
        // Décélération graduelle de la vitesse jusqu'à l'arrêt complet
        valueSpeed = FMath::FInterpTo(valueSpeed, 0.f, GetWorld()->DeltaTimeSeconds, 10.0f);
    }
    else // Si l'utilisateur presse une touche de mouvement
    {
        valueSpeed += (FMath::Abs(YValue) + FMath::Abs(XValue) * 10) * (10.2f * GetWorld()->DeltaTimeSeconds);
        valueSpeed = FMath::Clamp(valueSpeed, 0.f, 50.0f);
    }

    valueSpeedJoy = YValue + XValue;

    if (Controller && valueSpeed != 0.0f)
    {
        bEnableInterpolation = true;
        if (bEnableInterpolation)
        {
            // UE_LOG(LogTemp, Warning, TEXT("MoveForward pressed with value %f"), Value);
            //UE_LOG(LogTemp, Warning, TEXT("CurrentSpeed pressed with value %f"), valueSpeed);

            //const FVector Direction = FVector(XValue, YValue, 0.0f).GetSafeNormal();
            //const FRotator Rotation = FRotationMatrix::MakeFromXZ(Direction, FVector::CrossProduct(Direction, FVector::RightVector)).Rotator();

            //const FVector TargetLocation = GetActorLocation() + (Direction * (runSpeed * valueSpeed) * GetWorld()->DeltaTimeSeconds);
            //const FRotator TargetRotation = (TargetLocation - GetActorLocation()).Rotation();

            //SetActorLocationAndRotation(
                //FMath::VInterpTo(GetActorLocation(), TargetLocation, GetWorld()->DeltaTimeSeconds, 100.0f),
                //FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds, 100.0f)
            //);
        }
        else
        {
            AddMovementInput(FVector(1.0f, 0.0f, 0.0f), valueSpeedJoy);
        }
    }
}

void APlayerFight_Move::TurnCamera(const FInputActionValue& Value)
{
    const FVector2D CurrentValue = Value.Get<FVector2D>();

    PlayerController->AddYawInput(CurrentValue.X * 40.0f * GetWorld()->GetDeltaSeconds());
    PlayerController->AddPitchInput(CurrentValue.Y * 40.0f * GetWorld()->GetDeltaSeconds());
}
