// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "ClassList.h"

#include "Enemy_Stats.generated.h"

UCLASS()
class JONARYLGAME_API AEnemy_Stats : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Stats();


	UPROPERTY(EditAnywhere, meta = (MetaAttribute = "ClassList", DisplayName = "Classe ennemie"))
		EClassList ClassEnemy;

	FString Classe;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistiques")
		int Health;
	int Classe_Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistiques")
		int Attack;
	int Classe_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistiques")
		int Defense;
	int Classe_Defense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistiques")
		int MagicAttack;
	int Classe_MagicAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistiques")
		int MagicDefense;
	int Classe_MagicDefense;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistiques")
		float ArmorValue;
 
	int Classe_SpeedMove;
	int Classe_SpeedRotate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
