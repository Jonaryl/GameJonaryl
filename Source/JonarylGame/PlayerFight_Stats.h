// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "ClassList.h"

#include "PlayerFight_Stats.generated.h"

UCLASS()
class JONARYLGAME_API APlayerFight_Stats : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerFight_Stats();

	UPROPERTY(EditAnywhere, meta = (MetaAttribute = "Information", DisplayName = "Nom du personnage"))
		FString CharacterName;


	UPROPERTY(EditAnywhere, meta = (MetaAttribute = "ClassList", DisplayName = "Classe du personnage"))
		EClassList ClassCharacter;

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


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistiques Spe")
		int cutDamageStamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Statistiques Spe")
		float counterGaugeMax;
	float currentCounterGauge;

	int Classe_MagicDefense;

	int Classe_SpeedMove;
	int Classe_SpeedRotate;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool isSuperMode;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
