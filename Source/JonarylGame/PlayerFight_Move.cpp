// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Move.h"



#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Engine/LocalPlayer.h"
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
        UEnhancedInputLocalPlayerSubsystem * Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        if (Subsystem)
        {
            Subsystem->AddMappingContext(PlayerMappingContext, 0);
        }
    }
    // Initialisez le contrôleur de personnage
   //Controller = ACharacterController->GetController();
    //Controller = PlayerController->GetController();
}

void APlayerFight_Move::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerFight_Move::MoveForward);
        EnhancedInputComponent->BindAction(MoveCamera, ETriggerEvent::Triggered, this, &APlayerFight_Move::TurnCamera);
    }
    
    //PlayerInputComponent->BindAxis("LeftJsY", this, &APlayerFight_Move::MoveForward);
    //PlayerInputComponent->BindAxis("RightJsX", this, &APawn::AddControllerYawInput);
    //PlayerInputComponent->BindAxis("RightJsY", this, &APawn::AddControllerPitchInput);

    //UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent existe %f"), "Value");

}

void APlayerFight_Move::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (valueSpeedJoy == 0 && valueSpeed != 0)
    {
        valueSpeed = 0.0f;
        UE_LOG(LogTemp, Warning, TEXT("valueSpeedJoy %f"), valueSpeed);
    }
}

void APlayerFight_Move::MoveForward(const FInputActionValue& Value)
{
    const FVector2D CurrentValue = Value.Get<FVector2D>();

    valueSpeed += (FMath::Abs(CurrentValue.Y) + FMath::Abs(CurrentValue.X) * 10) * 10.2f * GetWorld()->DeltaTimeSeconds;
    valueSpeed = FMath::Clamp(valueSpeed, 0.f, 20.0f);

    valueSpeedJoy = CurrentValue.Y + CurrentValue.X;

    if (Controller && CurrentValue.Y + CurrentValue.X != 0.0f)
    {
        bEnableInterpolation = true;
        if (bEnableInterpolation)
        {
            // UE_LOG(LogTemp, Warning, TEXT("MoveForward pressed with value %f"), Value);
            UE_LOG(LogTemp, Warning, TEXT("CurrentSpeed pressed with value %f"), valueSpeed);
            const FRotator Rotation = Controller->GetControlRotation();
            const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

            const FVector TargetLocation = GetActorLocation() + (Direction * (runSpeed * valueSpeed) * GetWorld()->DeltaTimeSeconds);
            const FRotator TargetRotation = (TargetLocation - GetActorLocation()).Rotation();

            SetActorLocationAndRotation(
                FMath::VInterpTo(GetActorLocation(), TargetLocation, GetWorld()->DeltaTimeSeconds, 100.0f),
                FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds, 100.0f)
            );
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
