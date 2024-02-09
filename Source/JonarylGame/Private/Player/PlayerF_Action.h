// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerF_Move.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/PrimitiveComponent.h"

#include "States_PlayerF.h"

#include "PlayerF_Action.generated.h"

/**
 * 
 */
UCLASS()
class APlayerF_Action : public APlayerF_Move
{
	GENERATED_BODY()

protected:
	////////////////////////// BASE METHOD ///////////////////////////
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void NeutralAction() override;
	virtual void EndAllActionAnim() override;

	//////////////////////////// RAYCAST /////////////////////////////
	///// RAYCAST VARIABLE //////
	bool isGrounded;
	bool isNearGround;
	float distanceToGround;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Raycast")
		float distanceToBeGrounded;

	///// RAYCAST METHOD //////
	void GroundRaycast();

	//////////////////////////// JUMP /////////////////////////////
	///// JUMP VARIABLE //////
	int actionJumpTurn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump")
		int JumpUpMaxTurn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump")
		int JumpIdleMaxTurn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump")
		int JumpDownMaxTurn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump")
		int JumpDashMaxTurn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump")
		int JumpMoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump")
		int JumpForce;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Jump")
		int JumpDashForwardSpeed;

	////////////// JUMP ANIMATION VARIABLE /////////////
	bool isJumpUp;
	bool isJumpIdle;
	bool isJumpDown;
	bool isJumpDash;

	///// JUMP METHOD //////
	void ActionJumpUp();
	void ActionJumpIdle();
	void ActionJumpDown();
	void ActionJumpDash();
	void EndJump();

	//////////////////////////// DASH /////////////////////////////
	///// DASH VARIABLE //////
	int actionDashTurn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
		int dashMaxTurn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
		float dashForce;

	////////////// DASH ANIMATION VARIABLE /////////////
	bool isDash;
	int dashNumber;

	///// DASH METHOD //////
	void ActionDash();
	void EndDash();


	//////////////////////////// ADD FORCE /////////////////////////////
	void AddForce(int sens, int speedV, int speedH);

	//////////////////////////// INPUT /////////////////////////////
	virtual void ABtnAction() override;
	virtual void RBBtnAction() override;

	virtual void DebugBtnAction() override;
	//////////////////////////// GRAVITY /////////////////////////////

	virtual void CancelGravity();
	virtual void ActivateGravity();
	virtual void StopRootMotion();
	virtual void DisableFriction(float friction);

	/////////////////////////// DAMAGE ///////////////////////////
	bool canBeHit;

	////////////// DAMAGE ANIMATION VARIABLE /////////////
	bool isDamaged;

	virtual void DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, AActor* Enemy, float ArmorDamage, int damageId);
};
