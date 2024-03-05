// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerF_Move.h"

#include "GameplayTagContainer.h"
#include "Input/Events.h"

#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"


///////////////////////////////////////////////////////////////////
/////////////////////////// BASE METHOD ///////////////////////////
APlayerF_Move::APlayerF_Move()
{
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 600.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    FVector SpawnLocation = FVector(0.0f, 0.0f, 1.0f);
    FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
    SetActorLocationAndRotation(SpawnLocation, SpawnRotation);

    CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength, 100, 500);
}

void APlayerF_Move::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInputComponent)
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerF_Move::MoveForward);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &APlayerF_Move::StartMoving);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerF_Move::StopMoving);

        EnhancedInputComponent->BindAction(MoveCamera, ETriggerEvent::Triggered, this, &APlayerF_Move::TurnCamera);

        EnhancedInputComponent->BindAction(ABtn, ETriggerEvent::Triggered, this, &APlayerF_Move::ABtnAction);
        EnhancedInputComponent->BindAction(BBtn, ETriggerEvent::Triggered, this, &APlayerF_Move::BBtnAction);
        EnhancedInputComponent->BindAction(XBtn, ETriggerEvent::Triggered, this, &APlayerF_Move::XBtnAction);
        EnhancedInputComponent->BindAction(YBtn, ETriggerEvent::Triggered, this, &APlayerF_Move::YBtnAction);

        EnhancedInputComponent->BindAction(RBBtn, ETriggerEvent::Triggered, this, &APlayerF_Move::RBBtnAction);
        EnhancedInputComponent->BindAction(RBBtnHold, ETriggerEvent::Ongoing, this, &APlayerF_Move::RBBtnActionHold);
        EnhancedInputComponent->BindAction(RBBtnEnd, ETriggerEvent::Triggered, this, &APlayerF_Move::RBBtnActionEnd);

        EnhancedInputComponent->BindAction(DebugBtn, ETriggerEvent::Triggered, this, &APlayerF_Move::DebugBtnAction);
        //EnhancedInputComponent->BindAction(DeleteEnemyBtn, ETriggerEvent::Triggered, this, &APlayerFight_Move::RemoveAllEnemy);
    }

}

void APlayerF_Move::BeginPlay()
{
    Super::BeginPlay();

    canMove = true;
    canSprint = true;
    timeMoving = 0;

    sideMoving = 50.0f;
    timeStoppingMoving = 0.0f;

    PlayerController = Cast<APlayerController>(GetController());
    PlayerMesh = Cast<UPrimitiveComponent>(PlayerController->GetCharacter()->GetMesh());

    if (PlayerController)
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        if (Subsystem)
        {
            Subsystem->AddMappingContext(PlayerMappingContext, 0);
        }
    }

    if (PlayerFight_Lock)
        PlayerFight_LockInstance = NewObject<UComponent_PlayerF_Lock>(this, PlayerFight_Lock);

    if (PlayerFightHUDClass)
    {
        PlayerFightHUD = CreateWidget<UHUD_PlayerF>(GetWorld(), PlayerFightHUDClass);
        EnemyHUD = CreateWidget<UHUD_PlayerF>(GetWorld(), EnemyHUDClass);

        if (PlayerFightHUD)
            PlayerFightHUD->AddToPlayerScreen();
        if (EnemyHUD)
        {
            EnemyHUD->AddToPlayerScreen();
            EnemyHudIsVisible(false);
        }
    }
}
void APlayerF_Move::EndPlay(const EEndPlayReason::Type EndPlayerReason)
{
    Super::EndPlay(EndPlayerReason);
}
void APlayerF_Move::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (timeStoppingMoving > 0)
    {
        timeStoppingMoving--;
        speedStoppingMoving -= (100.2f * GetWorld()->DeltaTimeSeconds);

        const FVector ForwardVector = GetActorForwardVector();

        FVector AppliedForce = GetActorLocation() + (ForwardVector * speedStoppingMoving * forceStoppingMoving) * GetWorld()->DeltaTimeSeconds;
        SetActorLocation(
            FMath::VInterpTo(GetActorLocation(), AppliedForce, GetWorld()->DeltaTimeSeconds, 100.0f)
        );
    }
}

void APlayerF_Move::NeutralAction() {}
void APlayerF_Move::EndAllActionAnim() {}
void APlayerF_Move::EndPartialAction() {}
void APlayerF_Move::StopMovingAnim() {}
/////////////////////////// BASE METHOD ///////////////////////////
///////////////////////////////////////////////////////////////////

void APlayerF_Move::EnemyLockedIsDead() 
{ 
    enemyTargetLock = nullptr; 
}

///////////////////////////////////////////////////////////////////
/////////////////////////// MOVING ////////////////////////////////
MovementValues APlayerF_Move::XYGetValue(const FInputActionValue& Value)
{
    FVector2D CurrentValue = Value.Get<FVector2D>();
    const float XValue = CurrentValue.X;
    const float YValue = CurrentValue.Y;
    isMoveInput = true;

    if (CurrentValue.IsNearlyZero())
        valueSpeed = FMath::FInterpTo(valueSpeed, 0.f, GetWorld()->DeltaTimeSeconds, 10.0f);
    else
    {
        valueSpeed += (100.2f * GetWorld()->DeltaTimeSeconds);
        if (CurrentState == UStates_PlayerF::EStates_PlayerF::JumpUp ||
            CurrentState == UStates_PlayerF::EStates_PlayerF::IdleJump ||
            CurrentState == UStates_PlayerF::EStates_PlayerF::JumpDown)
            valueSpeed = FMath::Clamp(valueSpeed, 0.f, maxAirRunSpeed);
        else if (CurrentState == UStates_PlayerF::EStates_PlayerF::Sprint)
            valueSpeed = FMath::Clamp(valueSpeed, 0.f, maxSprintSpeed);
        else if (CurrentState == UStates_PlayerF::EStates_PlayerF::MoveSpe)
            valueSpeed = FMath::Clamp(valueSpeed, 0.f, maxRunSpeed/3);
        else
            valueSpeed = FMath::Clamp(valueSpeed, 0.f, maxRunSpeed);
    }

    FVector Direction = FVector(XValue, YValue, 0.0f);

    FRotator CamRotation = FollowCamera->GetComponentRotation();
    Direction = CamRotation.RotateVector(Direction);
    Direction.Z = 0.0f;

    FVector TargetLocation = GetActorLocation() + (Direction * ((runSpeed / 1.5) * valueSpeed) * GetWorld()->DeltaTimeSeconds);
    FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

    MovementValues Result;
    Result.XValue = XValue;
    Result.YValue = YValue;
    Result.TargetLocation = TargetLocation;
    Result.lookAtRotation = lookAtRotation;

    if (PlayerFight_LockInstance)
    {
        PlayerFight_LockInstance->Update(GetActorLocation(), TargetLocation);
        enemyTargetLock = PlayerFight_LockInstance->GetLastTarget();
    }

    ///DEBUG CUBE
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerF_Move::StaticClass(), FoundActors);
    for (AActor* Actor : FoundActors)
    {
        TArray<UStaticMeshComponent*> MeshComponents;
        Actor->GetComponents<UStaticMeshComponent>(MeshComponents);
        for (UStaticMeshComponent* MeshComponent : MeshComponents)
        {
            float OffsetDistance = 300.0f;
            FVector ForwardVector = GetActorForwardVector();
            FVector Offset = ForwardVector * OffsetDistance;

            FVector TargetLocationFar = TargetLocation + Offset;
            //UE_LOG(LogTemp, Warning, TEXT(" TargetLocation %s"), *TargetLocation.ToString());
            //UE_LOG(LogTemp, Warning, TEXT(" TargetLocationFar %s"), *TargetLocationFar.ToString());

            MeshComponent->SetWorldLocation(TargetLocation);
        }
    }
    ///////////////

    return Result;
}

FVector APlayerF_Move::GetPosition(FVector NewPosition)
{
    return FMath::VInterpTo(GetActorLocation(), NewPosition, GetWorld()->DeltaTimeSeconds, 100.0f);
}

FQuat APlayerF_Move::GetRotation(FVector TargetLocation)
{
    //FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
    return FQuat::Slerp(GetActorRotation().Quaternion(), MoveValue.lookAtRotation.Quaternion(), GetWorld()->DeltaTimeSeconds * runRotationSpeed);
}

void APlayerF_Move::Moving(FVector TargetLocation, FQuat InterpolatedRotation)
{
    if (CurrentState == UStates_PlayerF::EStates_PlayerF::Idle)
        SetCharacterState(UStates_PlayerF::EStates_PlayerF::Run, 0.0f);

    isMoving = true;

    //UE_LOG(LogTemp, Warning, TEXT(" TargetLocation = %s"), *TargetLocation.ToString());

    SetActorLocationAndRotation(
        FMath::VInterpTo(GetActorLocation(), TargetLocation, GetWorld()->DeltaTimeSeconds, 100.0f),
        FMath::RInterpTo(GetActorRotation(), InterpolatedRotation.Rotator(), GetWorld()->DeltaTimeSeconds, 100.0f)
    );
}

void APlayerF_Move::TurningTo(FVector destinationToLookAt, float speed)
{
    FVector DirectionToLook = destinationToLookAt - GetActorLocation();
    DirectionToLook.Z = 0.0f;
    FRotator LookAtRotation = FRotationMatrix::MakeFromX(DirectionToLook).Rotator();
    FRotator InterpolatedRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, GetWorld()->DeltaTimeSeconds, runRotationSpeed * speed);

    SetActorRotation(InterpolatedRotation);
}

void APlayerF_Move::ActionMovingAndTurning(FVector AppliedForce, float actionTurn, float force, float timeTurning)
{
    FVector Direction = MoveValue.TargetLocation;

    FQuat InterpolatedRotation = GetRotation(Direction);
    FRotator NewRotation = InterpolatedRotation.Rotator();
    NewRotation.Pitch = 0.0f;
    NewRotation.Roll = 0.0f;

    if (CurrentState == UStates_PlayerF::EStates_PlayerF::DashJump
        || CurrentState == UStates_PlayerF::EStates_PlayerF::Attack
        )
    {
        if (actionTurn > 0 && actionTurn < timeTurning)
        {
            FRotator finalRotation = InterpolatedRotation.Rotator();
            if (enemyTargetLock != nullptr && CurrentState == UStates_PlayerF::EStates_PlayerF::Attack)
            {

                FRotator lookAtRotationForTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), enemyTargetLock->GetActorLocation());
                FQuat InterpolatedRotationForTarget = FQuat::Slerp(GetActorRotation().Quaternion(), lookAtRotationForTarget.Quaternion(), GetWorld()->DeltaTimeSeconds * runRotationSpeed);

                float InterpAlpha = 0.2f;
                FQuat CombinedRotation = FQuat::Slerp(InterpolatedRotation, InterpolatedRotationForTarget, InterpAlpha);

                if (!isMoveInput)
                    finalRotation = InterpolatedRotationForTarget.Rotator();
                else
                    finalRotation = CombinedRotation.Rotator();
            }

            SetActorLocationAndRotation(
                AppliedForce,
                FMath::RInterpTo(GetActorRotation(), finalRotation, GetWorld()->DeltaTimeSeconds, force)
            );
        }
    }
    else
    {
        SetActorLocationAndRotation(
            AppliedForce,
            FMath::RInterpTo(GetActorRotation(), InterpolatedRotation.Rotator(), GetWorld()->DeltaTimeSeconds, 5.0f)
        );
    }

    
}
/////////////////////////// MOVING ////////////////////////////////
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
/////////////////////////// HUD //////////////////////////
void APlayerF_Move::EnemyHudIsVisible(bool isVisible)
{
    EnemyHUD->SetVisible(isVisible);
}
void APlayerF_Move::EditEnemyHealth(float enemyHealthMax, float enemyHealth)
{
    EnemyHUD->SetHealth(enemyHealthMax, enemyHealth);
}
void APlayerF_Move::EditEnemyArmor(float enemyArmorMax, float enemyArmor)
{
    EnemyHUD->SetClassPower(enemyArmorMax, enemyArmor);
}
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
/////////////////////////// INPUT METHOD //////////////////////////
// MOVE
void APlayerF_Move::StartMoving()
{ 
    //UE_LOG(LogTemp, Log, TEXT(" StartMoving"));
    if (CurrentState == UStates_PlayerF::EStates_PlayerF::Run || CurrentState == UStates_PlayerF::EStates_PlayerF::Idle
        || CurrentState == UStates_PlayerF::EStates_PlayerF::Sprint || CurrentState == UStates_PlayerF::EStates_PlayerF::Attack
        || CurrentState == UStates_PlayerF::EStates_PlayerF::CounterPose || CurrentState == UStates_PlayerF::EStates_PlayerF::Counter
        || CurrentState == UStates_PlayerF::EStates_PlayerF::Damage || CurrentState == UStates_PlayerF::EStates_PlayerF::AttackSpe
        || CurrentState == UStates_PlayerF::EStates_PlayerF::StanceSpe || CurrentState == UStates_PlayerF::EStates_PlayerF::MoveSpe
        )
    {
        if (canMove)
        {
            EndAllActionAnim();
            if (isMoving == false)
                isMoving = true;
            if (isIdle == true)
                isIdle = false;
            timeMoving = 0;
        }
    }
}
void APlayerF_Move::MoveForward(const FInputActionValue& Value)
{
    MoveValue = XYGetValue(Value);
    const float XValue = MoveValue.XValue;
    const float YValue = MoveValue.YValue;
    const FVector TargetLocation = MoveValue.TargetLocation;


    if (CurrentState == UStates_PlayerF::EStates_PlayerF::Run || CurrentState == UStates_PlayerF::EStates_PlayerF::Idle
        || CurrentState == UStates_PlayerF::EStates_PlayerF::Sprint || CurrentState == UStates_PlayerF::EStates_PlayerF::Attack
        || CurrentState == UStates_PlayerF::EStates_PlayerF::CounterPose || CurrentState == UStates_PlayerF::EStates_PlayerF::Counter 
        || CurrentState == UStates_PlayerF::EStates_PlayerF::Damage || CurrentState == UStates_PlayerF::EStates_PlayerF::AttackSpe
        || CurrentState == UStates_PlayerF::EStates_PlayerF::StanceSpe || CurrentState == UStates_PlayerF::EStates_PlayerF::MoveSpe
        )
    {
        if (Controller && valueSpeed != 0.0f && canMove)
        {
            if (CurrentState == UStates_PlayerF::EStates_PlayerF::Attack
                || CurrentState == UStates_PlayerF::EStates_PlayerF::CounterPose
                || CurrentState == UStates_PlayerF::EStates_PlayerF::Counter
                || CurrentState == UStates_PlayerF::EStates_PlayerF::Damage
                || CurrentState == UStates_PlayerF::EStates_PlayerF::AttackSpe
                )
            {
                EndAllActionAnim();
            }

            if (isSprint == false && isTimeMoving == true)
            {
                timeMoving++;
                if (timeMoving > 10)
                    isTimeMoving = false;
            }

            if (CurrentState == UStates_PlayerF::EStates_PlayerF::StanceSpe || CurrentState == UStates_PlayerF::EStates_PlayerF::AttackSpe)
                SetCharacterState(UStates_PlayerF::EStates_PlayerF::MoveSpe, 0.0f);
            else if (CurrentState != UStates_PlayerF::EStates_PlayerF::Run && CurrentState != UStates_PlayerF::EStates_PlayerF::Sprint 
                && CurrentState != UStates_PlayerF::EStates_PlayerF::MoveSpe)
                SetCharacterState(UStates_PlayerF::EStates_PlayerF::Run, 0.0f);

            FVector NewPosition = GetPosition(TargetLocation);
            FQuat InterpolatedRotation = GetRotation(TargetLocation);
            Moving(NewPosition, InterpolatedRotation);            
        }
    }
}
void APlayerF_Move::StopMoving()
{ 
    //UE_LOG(LogTemp, Log, TEXT(" StopMoving")); 
    isMoveInput = false;

    if (isSprint == true)
        isSprint = false;
    if (isMoving == true)
        isMoving = false;
    if (CurrentState == UStates_PlayerF::EStates_PlayerF::Run || CurrentState == UStates_PlayerF::EStates_PlayerF::Sprint)
    {
        if (isIdle == false)
            isIdle = true;
        SetCharacterState(UStates_PlayerF::EStates_PlayerF::Idle, 0.0f);

        if (CurrentState == UStates_PlayerF::EStates_PlayerF::Sprint || isTimeMoving == true)
            timeStoppingMoving = timeStoppingSprintMax;
        else
            timeStoppingMoving = timeStoppingMovingMax;
        speedStoppingMoving = maxRunSpeed;
    }
    timeMoving = 0;
}

// CAMERA
void APlayerF_Move::TurnCamera(const FInputActionValue& Value) 
{
    const FVector2D CurrentValue = Value.Get<FVector2D>();

    PlayerController->AddYawInput(CurrentValue.X * cameraSpeedRotationX * GetWorld()->GetDeltaSeconds());
    PlayerController->AddPitchInput(CurrentValue.Y * cameraSpeedRotationY * GetWorld()->GetDeltaSeconds());
}

// BUTTON
void APlayerF_Move::ABtnAction(){ UE_LOG(LogTemp, Log, TEXT(" ABtnAction")); }
void APlayerF_Move::BBtnAction(){ UE_LOG(LogTemp, Log, TEXT(" BBtnAction")); }
void APlayerF_Move::XBtnAction(){ UE_LOG(LogTemp, Log, TEXT(" XBtnAction")); }
void APlayerF_Move::YBtnAction(){ UE_LOG(LogTemp, Log, TEXT(" YBtnAction")); }


void APlayerF_Move::RBBtnAction(){ UE_LOG(LogTemp, Log, TEXT(" RBBtnAction")); }
void APlayerF_Move::RBBtnActionHold()
{
    if (isMoveInput && canSprint)
    {
        UE_LOG(LogTemp, Log, TEXT(" RBBtnActionHold")); 
        if (isMoveInput == true && CurrentState == UStates_PlayerF::EStates_PlayerF::Run ||
            isMoveInput == true && CurrentState == UStates_PlayerF::EStates_PlayerF::Sprint)
        {
            if (CurrentState != UStates_PlayerF::EStates_PlayerF::Sprint)
                SetCharacterState(UStates_PlayerF::EStates_PlayerF::Sprint, 0.0f);
            if(isSprint == false)
                isSprint = true;
            if(isTimeMoving == false)
                isTimeMoving = true;
        }
    }
}
void APlayerF_Move::RBBtnActionEnd()
{
    UE_LOG(LogTemp, Log, TEXT(" RBBtnActionEnd"));
    if (isMoveInput == true && CurrentState == UStates_PlayerF::EStates_PlayerF::Run ||
        isMoveInput == true && CurrentState == UStates_PlayerF::EStates_PlayerF::Sprint)
    {
        SetCharacterState(UStates_PlayerF::EStates_PlayerF::Run, 0.0f);
    }
    isSprint = false;
}


void APlayerF_Move::DebugBtnAction()
{
    UE_LOG(LogTemp, Error, TEXT(" MOVE "));
    UE_LOG(LogTemp, Warning, TEXT(" CurrentState = %d"), CurrentState);

    UE_LOG(LogTemp, Warning, TEXT(" isMoving = %s"), isMoving ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" isIdle = %s"), isIdle ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" isSprint = %s"), isSprint ? TEXT("True") : TEXT("False"));
}
/////////////////////////// INPUT METHOD //////////////////////////
///////////////////////////////////////////////////////////////////
 


///////////////////////////////////////////////////////////////////
/////////////////////////// STATES METHOD //////////////////////////
void APlayerF_Move::ChangeCharacterState(UStates_PlayerF::EStates_PlayerF NewState)
{
    CurrentState = NewState;
/*
*/
    if (SendMessage)
    {
        AActor* MessageInstance = GetWorld()->SpawnActor<AActor>(SendMessage, GetActorLocation(), GetActorRotation());

        ISendMessage_PlayerF_I* MessageInterface = Cast<ISendMessage_PlayerF_I>(MessageInstance);

        if (MessageInterface)
        {
            FStruct_SendMessage message;
            message.CurrentState = CheckStateInString(NewState);
            MessageInterface->Execute_ManagerSendState(MessageInstance, message);
        }
    }

    LogCurrentState();
}
FString APlayerF_Move::CheckStateInString(UStates_PlayerF::EStates_PlayerF NewState)
{
    FString stateString = "";

    switch (NewState) {
    case UStates_PlayerF::EStates_PlayerF::Idle:
        stateString = "Idle";
        break;
    case UStates_PlayerF::EStates_PlayerF::Run:
        stateString = "Run";
        break;
    case UStates_PlayerF::EStates_PlayerF::Sprint:
        stateString = "Sprint";
        break;
    case UStates_PlayerF::EStates_PlayerF::SuperRun:
        stateString = "SuperRun";
        break;
    case UStates_PlayerF::EStates_PlayerF::JumpUp:
        stateString = "JumpUp";
        break;
    case UStates_PlayerF::EStates_PlayerF::IdleJump:
        stateString = "IdleJump";
        break;
    case UStates_PlayerF::EStates_PlayerF::JumpDown:
        stateString = "JumpDown";
        break;
    case UStates_PlayerF::EStates_PlayerF::DashJump:
        stateString = "DashJump";
        break;
    case UStates_PlayerF::EStates_PlayerF::Attack:
        stateString = "Attack";
        break;
    case UStates_PlayerF::EStates_PlayerF::StanceSpe:
        stateString = "StanceSpe";
        break;
    case UStates_PlayerF::EStates_PlayerF::AttackSpe:
        stateString = "AttackSpe";
        break;
    case UStates_PlayerF::EStates_PlayerF::MoveSpe:
        stateString = "MoveSpe";
        break;
    case UStates_PlayerF::EStates_PlayerF::Dash:
        stateString = "Dash";
        break;
    case UStates_PlayerF::EStates_PlayerF::Dodge:
        stateString = "Dodge";
        break;
    case UStates_PlayerF::EStates_PlayerF::Damage:
        stateString = "Damage";
        break;
    case UStates_PlayerF::EStates_PlayerF::OnAir:
        stateString = "OnAir";
        break;
    case UStates_PlayerF::EStates_PlayerF::OnGround:
        stateString = "OnGround";
        break;
    case UStates_PlayerF::EStates_PlayerF::CounterPose:
        stateString = "CounterPose";
        break;
    case UStates_PlayerF::EStates_PlayerF::Counter:
        stateString = "Counter";
        break;
    case UStates_PlayerF::EStates_PlayerF::CounterAttack:
        stateString = "CounterAttack";
        break;
    case UStates_PlayerF::EStates_PlayerF::ChangeAction:
        stateString = "ChangeAction";
        break;
    default:
        break;
    }

    return stateString;
}

void APlayerF_Move::SetCharacterState(UStates_PlayerF::EStates_PlayerF NewState, float Time)
{
    FTimerHandle TimerHandle;
    FTimerDelegate TimerDel;
    TimerDel.BindUObject(this, &APlayerF_Move::ChangeCharacterState, NewState);
    if (Time == 0.0f)
        APlayerF_Move::ChangeCharacterState(NewState);
    else
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, Time, false);
}
/////////////////////////// STATES METHOD //////////////////////////
///////////////////////////////////////////////////////////////////

void APlayerF_Move::LogCurrentState()
{
    //UE_LOG(LogTemp, Log, TEXT("change d'etat CurrentState = %d"), CurrentState);
    UStates_PlayerF::EStates_PlayerF state = static_cast<UStates_PlayerF::EStates_PlayerF>(CurrentState);
    switch (state) {
    case UStates_PlayerF::EStates_PlayerF::Idle:
        UE_LOG(LogTemp, Log, TEXT("Idle"));
        break;
    case UStates_PlayerF::EStates_PlayerF::Run:
        UE_LOG(LogTemp, Log, TEXT("Run"));
        break;
    case UStates_PlayerF::EStates_PlayerF::Sprint:
        UE_LOG(LogTemp, Log, TEXT("Sprint"));
        break;
    case UStates_PlayerF::EStates_PlayerF::SuperRun:
        UE_LOG(LogTemp, Log, TEXT("SuperRun"));
        break;
    case UStates_PlayerF::EStates_PlayerF::JumpUp:
        UE_LOG(LogTemp, Log, TEXT("JumpUp"));
        break;
    case UStates_PlayerF::EStates_PlayerF::IdleJump:
        UE_LOG(LogTemp, Log, TEXT("IdleJump"));
        break;
    case UStates_PlayerF::EStates_PlayerF::JumpDown:
        UE_LOG(LogTemp, Log, TEXT("JumpDown"));
        break;
    case UStates_PlayerF::EStates_PlayerF::DashJump:
        UE_LOG(LogTemp, Log, TEXT("DashJump"));
        break;
    case UStates_PlayerF::EStates_PlayerF::Attack:
        UE_LOG(LogTemp, Log, TEXT("Attack"));
        break;
    case UStates_PlayerF::EStates_PlayerF::StanceSpe:
        UE_LOG(LogTemp, Log, TEXT("StanceSpe"));
        break;
    case UStates_PlayerF::EStates_PlayerF::MoveSpe:
        UE_LOG(LogTemp, Log, TEXT("MoveSpe"));
        break;
    case UStates_PlayerF::EStates_PlayerF::AttackSpe:
        UE_LOG(LogTemp, Log, TEXT("AttackSpe"));
        break;
    case UStates_PlayerF::EStates_PlayerF::Dash:
        UE_LOG(LogTemp, Log, TEXT("Dash"));
        break;
    case UStates_PlayerF::EStates_PlayerF::Dodge:
        UE_LOG(LogTemp, Log, TEXT("Dodge"));
        break;
    case UStates_PlayerF::EStates_PlayerF::Damage:
        UE_LOG(LogTemp, Log, TEXT("Damage"));
        break;
    case UStates_PlayerF::EStates_PlayerF::OnAir:
        UE_LOG(LogTemp, Log, TEXT("OnAir"));
        break;
    case UStates_PlayerF::EStates_PlayerF::OnGround:
        UE_LOG(LogTemp, Log, TEXT("OnGround"));
        break;
    case UStates_PlayerF::EStates_PlayerF::CounterPose:
        UE_LOG(LogTemp, Log, TEXT("CounterPose"));
        break;
    case UStates_PlayerF::EStates_PlayerF::Counter:
        UE_LOG(LogTemp, Log, TEXT("Counter"));
        break;
    case UStates_PlayerF::EStates_PlayerF::CounterAttack:
        UE_LOG(LogTemp, Log, TEXT("CounterAttack"));
        break;
    case UStates_PlayerF::EStates_PlayerF::ChangeAction:
        UE_LOG(LogTemp, Log, TEXT("ChangeAction"));
        break;
    default:
        break;
    }
    //UE_LOG(LogTemp, Log, TEXT("//////////////////////////////////"));
}



