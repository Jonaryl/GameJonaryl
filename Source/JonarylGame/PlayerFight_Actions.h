// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerFight_Move.h"

#include "Components/PrimitiveComponent.h"
#include "PlayerFight_States.h"

#include "PlayerFight_Actions.generated.h"

/**
 * 
 */
UCLASS()
class JONARYLGAME_API APlayerFight_Actions : public APlayerFight_Move
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerFight_Actions();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ActionTurn(bool isRotation);
	FRotator ActionTurnTargetRotation;

	//virtual void TakeDamage(int damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void CancelGravity() override;
	virtual void ActivateGravity() override;
	float jumpSpeed;
	float forwardSpeed;
	float dashSpeed;
	float DistanceToGround;
	int loopTurn;
	int dashNumber;

	virtual void ABtnAction() override;
	virtual void DebugBtnAction() override;

	virtual void RBBtnAction() override;
	//virtual void BButton() override;
	//virtual void XButton() override;
	//virtual void YButton() override;


	virtual bool GetisStartJump();
	virtual bool GetisIdleJump();
	virtual bool GetisDashJump();
	virtual bool GetisDash();
	virtual int GetdashNumber();

private:
		void JumpAction();
		void JumpDown();
		void DashAction();
	
};


