// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "PlayerFight_SpecialAttack.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JONARYLGAME_API UPlayerFight_SpecialAttack : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFight_SpecialAttack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SpecialAttack();

	virtual void StartSlowMotion(float slowStrength);
	virtual void EndSlowMotion();

	virtual void XBtnActionSpe();
	virtual void YBtnActionSpe();
	virtual void BBtnActionSpe();
	virtual void ABtnActionSpe();


	virtual void GetPlayer(AActor* player);
	////////////////////////////////////////// DEBUG //////////////////////////////////////////////////////
	virtual void AllEnemyEndSlow();
	virtual void RemoveAllEnemy();
};
