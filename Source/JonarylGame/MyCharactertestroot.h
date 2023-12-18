// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "ClassList.h"


#include "MyCharactertestroot.generated.h"

UCLASS()
class JONARYLGAME_API AMyCharactertestroot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharactertestroot();


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
