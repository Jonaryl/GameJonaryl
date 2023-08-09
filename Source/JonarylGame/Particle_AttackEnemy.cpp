// Fill out your copyright notice in the Description page of Project Settings.


#include "Particle_AttackEnemy.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AParticle_AttackEnemy::AParticle_AttackEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParticle_AttackEnemy::BeginPlay()
{
	Super::BeginPlay();
	LaunchParticle();
	if (CollisionAttack)
	{
		UE_LOG(LogTemp, Warning, TEXT("CollisionAttack detecter"));
		CollisionAttack->OnComponentBeginOverlap.AddDynamic(this, &AParticle_AttackEnemy::OnAttackCollisionBeginOverlap);
		CollisionAttack->OnComponentEndOverlap.AddDynamic(this, &AParticle_AttackEnemy::OnAttackCollisionEndOverlap);
	}

	float DelayBeforeDestroy = 0.3f;

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			UE_LOG(LogTemp, Error, TEXT("Destroy timer"));
			Destroy();
		}, DelayBeforeDestroy, false);
}

// Called every frame
void AParticle_AttackEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParticle_AttackEnemy::SetAttack_Implementation(int AttackPlayer, bool isRightAttack)
{
	UE_LOG(LogTemp, Warning, TEXT("SetAttack_Implementation SetAttack_Implementation"));

	playerAttack = AttackPlayer;
	isRightDamage = isRightAttack;
	UE_LOG(LogTemp, Warning, TEXT("playerAttack %f"), playerAttack);
	UE_LOG(LogTemp, Warning, TEXT("AttackPlayer %d"), AttackPlayer);


	if (CollisionAttack)
	{
		CollisionAttack->SetBoxExtent(CollisionSize);
		FString PositionString = CollisionSize.ToString();
		UE_LOG(LogTemp, Warning, TEXT("CollisionSize CollisionSize CollisionSize: %s"), *PositionString);
	}
}

void AParticle_AttackEnemy::OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *OtherActor->GetClass()->GetName());
		if (OtherActor->IsA(AEnemy_Unit::StaticClass()))
		{
			AEnemy_Unit* enemy = Cast<AEnemy_Unit>(OtherActor);
			if (enemy)
			{
				UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter on est bon plus qu'a"));
				DamageEnemy(enemy);
				Destroy();
			}
		}
	}
}

void AParticle_AttackEnemy::OnAttackCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("CollisionAttack c'est la fin"));
	// Handle the end of the overlap collision here
	// You can access the colliding actor (OtherActor) and perform any necessary logic
}

void AParticle_AttackEnemy::LaunchParticle()
{
	UE_LOG(LogTemp, Warning, TEXT("LaunchParticle oon est dans particle"));
	FVector PlayerPosition = GetActorLocation();
	FRotator PlayerRotation = GetActorRotation();

	// Calcul de la position relative de la particule devant le personnage
	FRotator CollisionRotation = ParticleRotation;
	CollisionRotation.Roll *= -1;

	FVector RelativePosition = PlayerPosition + PlayerRotation.RotateVector(ParticlePosition);
	FRotator RelativeRotation = CollisionRotation + PlayerRotation;

	SetActorLocation(RelativePosition);
	SetActorRotation(RelativeRotation);

	FVector PlayerForward = GetActorForwardVector();
	FVector RelativeParticulePosition = PlayerPosition + PlayerForward * ParticleDistance + PlayerRotation.RotateVector(ParticlePosition);

	FRotator ParticleRotationPlus = ParticleRotation;
	ParticleRotationPlus.Yaw += 180;
	ParticleRotationPlus.Roll *= 2;
	 
	FRotator RelativeParticuleRotation = UKismetMathLibrary::FindLookAtRotation(PlayerPosition, RelativeParticulePosition);
	FRotator FinalRelativeParticuleRotation = RelativeRotation + ParticleRotationPlus;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Particle, RelativeParticulePosition, FinalRelativeParticuleRotation);
	CollisionAttack = AParticle_AttackEnemy::FindComponentByClass<UBoxComponent>();

	if (CollisionAttack)
	{
		CollisionAttack->SetVisibility(true);
	}
}

void AParticle_AttackEnemy::DamageEnemy(AEnemy_Unit* enemy)
{
	bool finalDirectionIsRight;
	FVector enemyAttackDirection = enemy->GetActorLocation();
	FVector PlayerToEnemy = GetActorLocation() - enemyAttackDirection;
	PlayerToEnemy.Normalize();

	FVector PlayerForwardVector = enemy->GetActorForwardVector();
	FVector PlayerRightVector = enemy->GetActorRightVector();

	float ForwardDot = FVector::DotProduct(PlayerToEnemy, PlayerForwardVector);
	float RightDot = FVector::DotProduct(PlayerToEnemy, PlayerRightVector);

	if (FMath::Abs(ForwardDot) > FMath::Abs(RightDot))
	{
		if (ForwardDot < 0)
		{
			// Le coup vient de derrière
			finalDirectionIsRight = !isRightDamage;
			UE_LOG(LogTemp, Error, TEXT("dos dos dos dos "));
		}
		else
		{
			// Le coup vient de devant
			finalDirectionIsRight = isRightDamage;
			UE_LOG(LogTemp, Error, TEXT("face face face face "));
		}
	}
	else
	{
		if (RightDot < 0)
		{
			// Le coup vient de la gauche
			finalDirectionIsRight = false;
			UE_LOG(LogTemp, Error, TEXT("gauche gauche gauche gauche "));
		}
		else
		{
			// Le coup vient de la droite
			finalDirectionIsRight = true;
			UE_LOG(LogTemp, Error, TEXT("droite droite droite droite "));
		}
	}

	int FinalDamage = playerAttack + BaseDamage - enemy->Defense;
	UE_LOG(LogTemp, Warning, TEXT("DamageEnemy DamageEnemy"));
	enemy->DamageTake(FinalDamage, finalDirectionIsRight);
}


