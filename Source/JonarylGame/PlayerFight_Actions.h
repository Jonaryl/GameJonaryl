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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float jumpSpeed;
	float forwardSpeed;

	virtual void ABtnAction() override;
	//virtual void BButton() override;
	//virtual void XButton() override;
	//virtual void YButton() override;
	
};


