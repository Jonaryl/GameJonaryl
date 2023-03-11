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

#include "PlayerFight_States.h"

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

	APlayerFight_States::EPlayerFight_State CurrentState = APlayerFight_States::EPlayerFight_State::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bEnableInterpolation = true;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float maxRunSpeed = Classe_SpeedMove;
	int runSpeed = 20;
	UPROPERTY(EditAnywhere, Category = "Movement")
		int runRotationSpeed = 5 + Classe_SpeedRotate;
	
	float valueSpeed = 0.0f;
	float valueSpeedJoy = 0.0f;
	float InitialSpeed;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Landed(const FHitResult& Hit) override;

	//void MoveForward(float Value);
	void MoveForward(const FInputActionValue& Value);
	void TurnCamera(const FInputActionValue& Value);
	void StartMoving();
	void StopMoving();

	void MoveRight(float Value);


protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetCharacterState(APlayerFight_States::EPlayerFight_State NewState);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* PlayerMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* MoveCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* ABtn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* BBtn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* XBtn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* YBtn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* RBBtn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* LBBtn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* RTBtn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* LTBtn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* TopBtn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* BottomBtn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* LeftBtn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* RightBtn;


	APlayerController* PlayerController;
	UEnhancedInputComponent* EnhancedInputComponent;
	bool isMoveInput;

	float XMoveDirection;
	float YMoveDirection;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TEST")
		UStaticMeshComponent* MyMeshTest;


	virtual void ABtnAction();
	//virtual void BButton();
	//virtual void XButton();
	//virtual void YButton();

	virtual float GetSpeed();
	virtual bool GetisIdle();
	virtual bool GetisNearGround();

	bool isStartJump;
	bool isIdleJump;
	bool isDashJump;
	bool isNearGround;

	bool isIdle;
};
