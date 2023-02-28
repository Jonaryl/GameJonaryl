// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFight_Move.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"


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

    //APlayerController* PlayerController = Cast<APlayerController>(GetController());
    //if (PlayerController)
    //{
       // UEnhancedInputLocalPlayerSubSystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubSystem>(PlayerController->GetLocalPlayer());
       // if (Subsystem)
       // {
           // Subsystem->AddMappingContext(PlayerMappingContext, 0)
       // }
   // }
    // Initialisez le contrôleur de personnage
   //Controller = ACharacterController->GetController();
}

void APlayerFight_Move::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    
    //if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
   // {
       // EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerFight_Move::MoveForward);
    //}
    
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

//void APlayerFight_Move::MoveForward(const FInputActionValue& Value)
void APlayerFight_Move::MoveForward(float Value)
{
    //const CurrentValue = Value.Get<FVector2D>();

    //valueSpeed += (CurrentValue.y + CurrentValue.x *100) * 100.2f * GetWorld()->DeltaTimeSeconds;
    //valueSpeed = FMath::Clamp(valueSpeed, 0.f, 2000.0f);

    //valueSpeedJoy = CurrentValue.y + CurrentValue.x;

    //if (Controller && CurrentValue.y + CurrentValue.x != 0.0f)
    //{
        bEnableInterpolation = true;
        if (bEnableInterpolation)
        {
            // UE_LOG(LogTemp, Warning, TEXT("MoveForward pressed with value %f"), Value);
            UE_LOG(LogTemp, Warning, TEXT("CurrentSpeed pressed with value %f"), valueSpeed);
            const FRotator Rotation = Controller->GetControlRotation();
            const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

            const FVector TargetLocation = GetActorLocation() + (Direction * Value * (runSpeed + valueSpeed) * GetWorld()->DeltaTimeSeconds);
            const FRotator TargetRotation = Direction.Rotation();

            SetActorLocationAndRotation(
                FMath::VInterpTo(GetActorLocation(), TargetLocation, GetWorld()->DeltaTimeSeconds, 100.0f),
                FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds, 100.0f)
            );
        }
        else 
        {
            AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
        }
   // }
}
