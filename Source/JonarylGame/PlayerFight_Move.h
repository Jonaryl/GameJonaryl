// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerFight_Classes.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"
#include "Components/InputComponent.h"


#include "inputActionValue.h"

#include "PlayerFight_Move.generated.h"


class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class JONARYLGAME_API APlayerFight_Move : public APlayerFight_Classes
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerFight_Move();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bEnableInterpolation = true;

	UPROPERTY(EditAnywhere, Category = "Movement")
		int runSpeed = 5 + Classe_SpeedMove;
	UPROPERTY(EditAnywhere, Category = "Movement")
		int runRotationSpeed = 5 + Classe_SpeedRotate;
	
	float valueSpeed = 0.0f;
	float valueSpeedJoy = 0.0f;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//void MoveForward(float Value);
	void MoveForward(const FInputActionValue& Value);
	void TurnCamera(const FInputActionValue& Value);

	void MoveRight(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* PlayerMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* MoveCamera;

	APlayerController* PlayerController;
	UEnhancedInputComponent* EnhancedInputComponent;
	bool isMoveInput;
	
};
