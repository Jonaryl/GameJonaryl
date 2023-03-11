// Fill out your copyright notice in the Description page of Project Settings.


#include  "DrawDebugHelpers.h"
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
    
    if (CurrentState == APlayerFight_States::EPlayerFight_State::Jump || CurrentState == APlayerFight_States::EPlayerFight_State::DashJump)
    {
        int sens = 1;
        if (CurrentState == APlayerFight_States::EPlayerFight_State::DashJump)
        {
            sens = -1;
            forwardSpeed = 5000;
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

        /////////////////// raycast ///////////////////////////////////////////////////////// 

        float GroundCheckDistance = 300.0f;
        FVector StartLocation = GetActorLocation();
        FVector EndLocation = StartLocation - FVector(0.0f, 0.0f, GroundCheckDistance);
        FHitResult HitResult;
        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(this);

        //DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 0.1f, 0, 2.0f);
        bool bIsGrounded = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams);

        if (bIsGrounded)
        {
            float DistanceToGround = HitResult.Distance;
            if (DistanceToGround < 120)
            {
               // UE_LOG(LogTemp, Warning, TEXT("raycast - 120"));
                //SetCharacterState(APlayerFight_States::EPlayerFight_State::Idle);
            }
        }
        /////////////////// raycast ///////////////////////////////////////////////////////// 

        PlayerController->GetCharacter()->GetCharacterMovement()->AddForce(force);

        // Contrôler la vitesse du saut
        if (jumpSpeed > 2000000.0f && CurrentState != APlayerFight_States::EPlayerFight_State::DashJump)
        {
            jumpSpeed = 50000.0f;
            if (forwardSpeed != 0)
                forwardSpeed = 90000.0f;
        }
        else if (jumpSpeed > 0.0f) 
        {
            jumpSpeed -= 50000.0f * GetWorld()->GetDeltaSeconds();
            if (forwardSpeed != 0 && CurrentState != APlayerFight_States::EPlayerFight_State::DashJump)
                forwardSpeed -= 50000.0f * GetWorld()->GetDeltaSeconds();
            else if (CurrentState == APlayerFight_States::EPlayerFight_State::DashJump)
                forwardSpeed -= 5000.0f * GetWorld()->GetDeltaSeconds();
        }
        else {
            jumpSpeed = 0.0f;
            isStartJump = false;
            isIdleJump = true;
            SetCharacterState(APlayerFight_States::EPlayerFight_State::IdleJump);
        }
    }
}

void APlayerFight_Actions::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (EnhancedInputComponent)
    {
        //EnhancedInputComponent->BindAction(ABtn, ETriggerEvent::Triggered, this, &APlayerFight_Actions::ABtnAction); // space
        //EnhancedInputComponent->BindAction(BBtn, ETriggerEvent::Triggered, this, &APlayerFight_Actions::BButton); // A
        //EnhancedInputComponent->BindAction(XBtn, ETriggerEvent::Triggered, this, &APlayerFight_Actions::XButton); // E
        //EnhancedInputComponent->BindAction(YBtn, ETriggerEvent::Triggered, this, &APlayerFight_Actions::YButton); // R

    }
}


void APlayerFight_Actions::ABtnAction()
{
    //UE_LOG(LogTemp, Warning, TEXT(" CurrentState action = %d"), CurrentState);

    if (CurrentState != APlayerFight_States::EPlayerFight_State::Jump && CurrentState != APlayerFight_States::EPlayerFight_State::IdleJump && 
        CurrentState != APlayerFight_States::EPlayerFight_State::DashJump)
    {
        //UE_LOG(LogTemp, Warning, TEXT(" Jump action = %d"), CurrentState);
        jumpSpeed = 2400000.0f;
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
            SetCharacterState(APlayerFight_States::EPlayerFight_State::Jump);
            isStartJump = true;
        }
        else {
            UE_LOG(LogTemp, Error, TEXT("PlayerMesh is null"));
        }
    }
    else if (CurrentState == APlayerFight_States::EPlayerFight_State::IdleJump || CurrentState == APlayerFight_States::EPlayerFight_State::Jump)
    {
        //UE_LOG(LogTemp, Warning, TEXT(" CurrentState IdleJump = %d"), CurrentState);
        jumpSpeed = 3600000.0f;
 
        forwardSpeed = 0.0f;

        if (PlayerController->GetCharacter() && PlayerController->GetCharacter()->GetCharacterMovement())
        {
            UE_LOG(LogTemp, Warning, TEXT(" CurrentState PlayerController = %d"), CurrentState);
            UE_LOG(LogTemp, Error, TEXT("DashJump"));
            SetCharacterState(APlayerFight_States::EPlayerFight_State::DashJump);
        }
        else {
            UE_LOG(LogTemp, Error, TEXT("PlayerMesh is null"));
        }
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