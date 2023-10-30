// Fill out your copyright notice in the Description page of Project Settings.


#include "Particle_AttackPlayer.h"

AParticle_AttackPlayer::AParticle_AttackPlayer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AParticle_AttackPlayer::BeginPlay()
{
	Super::BeginPlay();
	LaunchParticle();
	if (CollisionAttack)
	{
		CollisionAttack->OnComponentBeginOverlap.AddDynamic(this, &AParticle_AttackPlayer::OnAttackCollisionBeginOverlap);
		CollisionAttack->OnComponentEndOverlap.AddDynamic(this, &AParticle_AttackPlayer::OnAttackCollisionEndOverlap); 
	}

	float DelayBeforeDestroy = 0.15f;

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this]()
		{
			UE_LOG(LogTemp, Error, TEXT("Destroy timer"));
			Destroy();
		}, DelayBeforeDestroy, false);
}


void AParticle_AttackPlayer::SetAttack_Implementation(int AttackEnemy, bool isRightAttack, FVector enemyPosition, AActor* Enemy)
{
	enemyAttack = AttackEnemy;
	isRightDamage = isRightAttack;
	EnemyLaunchPosition = enemyPosition;
	CurrentEnemy = Enemy;

	if (CollisionAttack)
	{
		CollisionAttack->SetBoxExtent(CollisionSize);
	}
}

void AParticle_AttackPlayer::OnAttackCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		if (OtherActor->IsA(APlayerFight_Character::StaticClass()))
		{
			// La collision concerne un acteur de la classe APlayerCharacter
			APlayerFight_Character* PlayerCharacter = Cast<APlayerFight_Character>(OtherActor);
			if (PlayerCharacter)
			{
				DamagePlayer(PlayerCharacter);
				Destroy();
			}
		}
	}
}

void AParticle_AttackPlayer::OnAttackCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Handle the end of the overlap collision here
	// You can access the colliding actor (OtherActor) and perform any necessary logic
}

// Called every frame
void AParticle_AttackPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Called every frame
void AParticle_AttackPlayer::LaunchParticle()
{
	FVector EnemyPosition = GetActorLocation();
	FRotator EnemyRotation = GetActorRotation();

	// Calcul de la position relative de la particule devant le personnage

	// Calcul de la position relative de la particule devant le personnage
	FRotator CollisionRotation = ParticleRotation;
	CollisionRotation.Roll *= -1;

	FVector RelativePosition = EnemyPosition + EnemyRotation.RotateVector(ParticlePosition);
	FRotator RelativeRotation = CollisionRotation + EnemyRotation;

	SetActorLocation(RelativePosition);
	SetActorRotation(RelativeRotation);

	FVector PlayerForward = GetActorForwardVector();
	FVector RelativeParticulePosition = EnemyPosition + PlayerForward * ParticleDistance + EnemyRotation.RotateVector(ParticlePosition);

	FRotator ParticleRotationPlus = ParticleRotation;
	ParticleRotationPlus.Yaw += 180;
	ParticleRotationPlus.Roll *= 2;

	FRotator RelativeParticuleRotation = UKismetMathLibrary::FindLookAtRotation(EnemyPosition, RelativeParticulePosition);
	FRotator FinalRelativeParticuleRotation = RelativeRotation + ParticleRotationPlus;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Particle, RelativeParticulePosition, FinalRelativeParticuleRotation);
	CollisionAttack = AParticle_AttackPlayer::FindComponentByClass<UBoxComponent>();

	if (CollisionAttack)
	{
		//CollisionAttack->SetVisibility(true);
	}
}


void AParticle_AttackPlayer::DamagePlayer(APlayerFight_Character* player)
{
	bool finalDirectionIsRight;
	FVector playerAttackDirection = player->GetActorLocation();
	FVector PlayerToEnemy = GetActorLocation() - playerAttackDirection;
	PlayerToEnemy.Normalize();

	FVector PlayerForwardVector = player->GetActorForwardVector();
	FVector PlayerRightVector = player->GetActorRightVector();

	float ForwardDot = FVector::DotProduct(PlayerToEnemy, PlayerForwardVector);
	float RightDot = FVector::DotProduct(PlayerToEnemy, PlayerRightVector);

	if (FMath::Abs(ForwardDot) > FMath::Abs(RightDot))
	{
		if (ForwardDot < 0)
		{
			// Le coup vient de derrière
			finalDirectionIsRight = !isRightDamage;
			//UE_LOG(LogTemp, Error, TEXT("dos dos dos dos "));
		}
		else
		{
			// Le coup vient de devant
			finalDirectionIsRight = isRightDamage;
			//UE_LOG(LogTemp, Error, TEXT("face face face face "));
		}
	}
	else
	{
		if (RightDot < 0)
		{
			// Le coup vient de la gauche
			finalDirectionIsRight = false;
			//UE_LOG(LogTemp, Error, TEXT("gauche gauche gauche gauche "));
		}
		else
		{
			// Le coup vient de la droite
			finalDirectionIsRight = true;
			//UE_LOG(LogTemp, Error, TEXT("droite droite droite droite "));
		}
	}

	int FinalDamage = enemyAttack + BaseDamage - player->Defense;
	player->DamageTake(FinalDamage, finalDirectionIsRight, isDamageCut, damageCut, CurrentEnemy);
}

