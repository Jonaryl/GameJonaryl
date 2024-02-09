// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerF_Classe.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"
#include "EngineUtils.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"
#include "Components/InputComponent.h"
#include "TimerManager.h"

#include "States_PlayerF.h"
#include "Player/SendMessage_PlayerF_I.h"
#include "Player/Component_PlayerF_Lock.h"
#include "../Huds/HUD_PlayerF.h"
#include "Structures/Struct_SendMessage.h"

#include "PlayerF_Move.generated.h"

class UInputMappingContext;
class UInputAction;

struct MovementValues
{
	float XValue;
	float YValue;
	FVector TargetLocation;
	FRotator lookAtRotation;
};

/**
 * 
 */
UCLASS()
class APlayerF_Move : public APlayerF_Classe
{
	GENERATED_BODY()

public:

	/////////////////////////// CAMERA //////////////////////////
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* FollowCamera;


protected:

	/////////////////////////// BASE METHOD ///////////////////////////
	APlayerF_Move();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayerReason)override;
	virtual void Tick(float DeltaTime) override;

	// ANIMATIONS AND LOCKS RESET
	virtual void NeutralAction();
	virtual void EndAllActionAnim();
	virtual void EndPartialAction();
	virtual void StopMovingAnim();

	/////////////////////////// BASE Variable ///////////////////////////
	APlayerController* PlayerController;
	UPrimitiveComponent* PlayerMesh;

	/////////////////////////// MOVING ///////////////////////////
	///// MOVING VARIABLE //////
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float maxRunSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float maxSprintSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float maxAirRunSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float runSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float runRotationSpeed;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float forceStoppingMoving;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Moving")
		float timeStoppingMovingMax;
	float timeStoppingMoving;
	float speedStoppingMoving;

	bool isMoveInput;
	bool isSprintInput;
	bool canMove;
	bool canSprint;

	float XMoveDirection;
	float YMoveDirection;
	MovementValues MoveValue;

	float valueSpeed = 0.0f;

	float valueSpeedJoy = 0.0f;
	float InitialSpeed;
	float valueTurn = 50.0f;

	float timeMoving;
	bool isTimeMoving;

	////////////// MOVING ANIMATION VARIABLE /////////////
	bool isIdle;
	bool isMoving;
	bool isSprint;
	float sideMoving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lock")
		TSubclassOf<UComponent_PlayerF_Lock> PlayerFight_Lock;
	UComponent_PlayerF_Lock* PlayerFight_LockInstance;

	AActor* enemyTargetLock;

	///// MOVING METHOD //////
	MovementValues XYGetValue(const FInputActionValue& Value);

	FVector GetPosition(FVector NewPosition);
	FQuat GetRotation(FVector TargetLocation);
	void Moving(FVector TargetLocation, FQuat InterpolatedRotation);
	//void Turning(FRotator NewRotation, float force);
	void ActionMovingAndTurning(FVector AppliedForce, float actionTurn, float force, float timeTurning);

	void TurningTo(FVector destinationToLookAt, float speed = 1.0f);
	/////////////////////////// STATES ///////////////////////////
	UStates_PlayerF::EStates_PlayerF CurrentState = UStates_PlayerF::EStates_PlayerF::Idle;

	virtual void SetCharacterState(UStates_PlayerF::EStates_PlayerF NewState, float Time);
	virtual void ChangeCharacterState(UStates_PlayerF::EStates_PlayerF NewState);

	UPROPERTY(EditAnywhere, Category = "SendMessage")
		TSubclassOf<AActor> SendMessage;
	FString CheckStateInString(UStates_PlayerF::EStates_PlayerF NewState);

	/////////////////////////// HUD ///////////////////////////
	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<class UHUD_PlayerF> PlayerFightHUDClass;
	UPROPERTY()
		class UHUD_PlayerF* PlayerFightHUD;

	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<class UHUD_PlayerF> EnemyHUDClass;
	UPROPERTY()
		class UHUD_PlayerF* EnemyHUD;
public:
	void EditEnemyHealth(float enemyHealthMax, float enemyHealth);
	void EditEnemyArmor(float enemyArmorMax, float enemyArmor);
	void EnemyHudIsVisible(bool isVisible);
protected:
	/////////////////////////// INPUT ///////////////////////////
	
	///// INPUT METHOD //////
		// MOVE
		void MoveForward(const FInputActionValue& Value);
		void StartMoving();
		void StopMoving();
		// CAMERA
		void TurnCamera(const FInputActionValue& Value);
		// BUTTON
		virtual void ABtnAction();
		virtual void BBtnAction();
		virtual void XBtnAction();
		virtual void YBtnAction();

		virtual void RBBtnAction();
		virtual void RBBtnActionHold();
		virtual void RBBtnActionEnd();

		virtual void DebugBtnAction();
	///// INPUT METHOD //////


	// method bind
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UEnhancedInputComponent* EnhancedInputComponent;

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
		UInputAction* RBBtnHold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* RBBtnEnd;

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


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* DebugBtn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
		UInputAction* DeleteEnemyBtn;


	////// DEBUG
	void LogCurrentState();
};
