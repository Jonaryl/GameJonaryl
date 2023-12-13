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
#include "Blueprint/UserWidget.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"
#include "Components/InputComponent.h"
#include "TimerManager.h"

#include "inputActionValue.h"

#include "PlayerFight_States.h"
#include "PlayerFight_Lock.h"
#include "PlayerFight_HUD.h"


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
	float valueTurn = 50.0f;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Landed(const FHitResult& Hit) override;

	//void MoveForward(float Value);
	void MoveForward(const FInputActionValue& Value);
	void TurnCamera(const FInputActionValue& Value);
	void StartMoving();
	void StopMoving();

	void MoveRight(float Value);

	// HUD //
	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<class UPlayerFight_HUD> PlayerFightHUDClass;
	UPROPERTY()
		class UPlayerFight_HUD* PlayerFightHUD;

	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<class UPlayerFight_HUD> EnemyHUDClass;
	UPROPERTY()
		class UPlayerFight_HUD* EnemyHUD;
	
	void EditEnemyHealth(float enemyHealthMax, float enemyHealth);
	void EditEnemyArmor(float enemyArmorMax, float enemyArmor);
	void EnemyHudIsVisible(bool isVisible);

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayerReason)override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetCharacterState(APlayerFight_States::EPlayerFight_State NewState, float Time);
	virtual void ChangeCharacterState(APlayerFight_States::EPlayerFight_State NewState);
	//virtual void ChangeCharacterState(void* NewStatePtr);

	virtual void Rotating();
	virtual void RotatingFormDirection(FQuat InterpolatedRotationFormDirection);
	FVector TargetLocation;
	FQuat InterpolatedRotation;

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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Particle)
		TSubclassOf<UPlayerFight_Lock> PlayerFight_Lock;
	UPlayerFight_Lock* PlayerFight_LockInstance;


	APlayerController* PlayerController;
	UEnhancedInputComponent* EnhancedInputComponent;
	UPrimitiveComponent* PlayerMesh;
	bool isMoveInput;
	bool isSprintInput;
	bool canMove;

	float currentHealth;

	bool canMoveWhenCombo;

	bool canBeHit;
	float canBeHitCoolDown;

	bool canTurnAction;
	float canTurnActionCoolDown;

	float XMoveDirection;
	float YMoveDirection;

	bool canDash = true;
	bool bIsGrounded;
	virtual void CancelGravity();
	virtual void ActivateGravity();

	virtual void ABtnAction();
	virtual void BBtnAction();
	virtual void XBtnAction();
	virtual void YBtnAction();

	virtual void RBBtnAction();
	virtual void RBBtnActionHold();
	virtual void RBBtnActionEnd();


	virtual void EndAnimation();

	virtual void DebugBtnAction();
	//virtual void BButton();
	//virtual void XButton();
	//virtual void YButton();

	virtual float GetSpeed();
	virtual bool GetisIdle();
	virtual bool GetisSprint();
	virtual bool GetisNearGround();
	virtual bool GetCanMove();
	virtual bool GetisMoving();
	virtual bool GethasLanded();

	bool isStartJump;
	bool isIdleJump;
	bool hasLanded;
	bool isDashJump;
	bool isDash;
	bool isNearGround;
	bool isSprint;
	bool isMoving;


	bool isAttacking;
	bool RootMotionProblem;

	bool isIdle;


	////////////////////////////////////////// DEBUG //////////////////////////////////////////////////////
	virtual void RemoveAllEnemy();
};
