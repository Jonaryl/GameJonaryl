// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemies_Behaviors.h"

void AEnemies_Behaviors::BeginPlay()
{
	Super::BeginPlay();
	behaviorValues.isActionEnded = false;
	behaviorValues.timeBehavior = 0.0f;

	if (ListBehaviors.IsEmpty())
	{
		if (canChasing)
		{
			for (int i = probabilityChasing; i > 0; i--)
				ListBehaviors.Add("Chasing");
		}
		if (canAttack)
		{
			for (int i = probabilityAttack; i > 0; i--)
				ListBehaviors.Add("Attack");
		}
		if (canTurningAround)
		{
			for (int i = probabilityTurningAround; i > 0; i--)
				ListBehaviors.Add("TurningAround");
		}
		if (canEvaluate)
		{
			for (int i = probabilityEvaluate; i > 0; i--)
				ListBehaviors.Add("Evaluate");
		}
	}
	if (ListReactionsBehaviors.IsEmpty())
	{
		if (canDodgeProba)
		{
			for (int i = probabilityDodge; i > 0; i--)
				ListReactionsBehaviors.Add("Dodge");
		}
		if (canCounterProba)
		{
			for (int i = probabilityCounter; i > 0; i--)
				ListReactionsBehaviors.Add("Counter");
		}
	}

	WaitingTimeBetwenAction();
	UE_LOG(LogTemp, Warning, TEXT(" CurrentBehaviorsState = %d"), CurrentBehaviorsState);
}

void AEnemies_Behaviors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//IsInterrupted
	if (CurrentBehaviorsState != UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::Dead)
	{
		if (CurrentBehaviorsState == UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::IsInterrupted)
		{
			if (CurrentActionState == UStates_EnemiesActions::EStates_EnemiesActions::Damage && currentDamagedCooldown >= 0)
			{
				currentDamagedCooldown--;
				if (currentDamagedCooldown == 0)
				{
					SetBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::WaitingNextAction, 0.0f);
					WaitingTimeBetwenAction();
				}
			}
			if (CurrentActionState == UStates_EnemiesActions::EStates_EnemiesActions::Dead && deathAnimationCooldown >= 0)
			{
				deathAnimationCooldown--;
				if (deathAnimationCooldown <= 0)
				{
					SetBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::Dead, 0.0f);					
					SendMessageManager();
				}
			}
		}
		//CHASING PLAYER
		else if (CurrentBehaviorsState == UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::ChasingPlayer)
		{
			if (behaviorValues.timeBehavior < 600.0f && behaviorValues.isActionEnded == false)
			{
				if(CurrentPlayerState == UStates_PlayerF::EStates_PlayerF::Run)
					MoveToPlayer(1.2f, UStates_EnemiesActions::EStates_EnemiesActions::Run);
				else if(CurrentPlayerState == UStates_PlayerF::EStates_PlayerF::Sprint)
					MoveToPlayer(1.8f, UStates_EnemiesActions::EStates_EnemiesActions::Sprint);
				else
					MoveToPlayer(0.8f, UStates_EnemiesActions::EStates_EnemiesActions::Walk);
			}
			else
				WaitingTimeBetwenAction();
		}
		//DODGE ATTACK PLAYER
		else if (CurrentBehaviorsState == UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::DodgeAttack)
		{
			//if (behaviorValues.timeBehavior < 100.0f && behaviorValues.isActionEnded == false)
			if (behaviorValues.isActionEnded == false)
			{
				DodgeAttack();
			}
			else
			{
				canBeHit = true;
				WaitingTimeBetwenAction();
			}
		}
		//COUNTER ATTACK PLAYER
		else if (CurrentBehaviorsState == UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::CounterAttack)
		{
			if (behaviorValues.isActionEnded == false)
			{
				CounterAttack();
			}
			else
				WaitingTimeBetwenAction();
		}
		//ATTACK PLAYER
		else if (CurrentBehaviorsState == UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::AttackPlayer)
		{
			if (behaviorValues.isActionEnded == false)
			{
				float playerDistance = GetPlayerDistance();
				if (playerDistance > distanceToStopToPlayer && CurrentActionState != UStates_EnemiesActions::EStates_EnemiesActions::Attack)
				{
					if (CurrentPlayerState == UStates_PlayerF::EStates_PlayerF::Run)
						MoveToPlayer(1.0f, UStates_EnemiesActions::EStates_EnemiesActions::Run);
					else if (CurrentPlayerState == UStates_PlayerF::EStates_PlayerF::Sprint)
						MoveToPlayer(1.0f, UStates_EnemiesActions::EStates_EnemiesActions::Sprint);
					else
						MoveToPlayer(1.0f, UStates_EnemiesActions::EStates_EnemiesActions::Walk);
				}
				else
					AttackPlayer();
			}
			else
				WaitingTimeBetwenAction();
		}
		//CAUTIOUS MOVING
		else if (CurrentBehaviorsState == UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::TurnAroundPlayer)
		{
			if (behaviorValues.isActionEnded == false)
			{
				float playerDistance = GetPlayerDistance();
				if (playerDistance > (distanceTurnPlayer * distanceToStopToPlayer))
				{
					if (CurrentPlayerState == UStates_PlayerF::EStates_PlayerF::Run)
						MoveToPlayer((distanceTurnPlayer), UStates_EnemiesActions::EStates_EnemiesActions::Run);
					else if (CurrentPlayerState == UStates_PlayerF::EStates_PlayerF::Sprint)
						MoveToPlayer((distanceTurnPlayer), UStates_EnemiesActions::EStates_EnemiesActions::Sprint);
					else
						MoveToPlayer((distanceTurnPlayer), UStates_EnemiesActions::EStates_EnemiesActions::Walk);
				}
				else
					TurningAroundPlayer((distanceTurnPlayer), UStates_EnemiesActions::EStates_EnemiesActions::Run);
			}
			else
				WaitingTimeBetwenAction();
		}
		//TURNING AROUND PLAYER
		else if (CurrentBehaviorsState == UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::EvaluatePlayer)
		{
			if (behaviorValues.isActionEnded == false)
			{
				if (CurrentPlayerState == UStates_PlayerF::EStates_PlayerF::Run)
					MoveToPlace(UStates_EnemiesActions::EStates_EnemiesActions::Run);
				else if (CurrentPlayerState == UStates_PlayerF::EStates_PlayerF::Sprint)
					MoveToPlace(UStates_EnemiesActions::EStates_EnemiesActions::Sprint);
				else
					MoveToPlace(UStates_EnemiesActions::EStates_EnemiesActions::Walk);
			}
			else
			{
				int randomChoice = GenerateRandomInt(1, 100);

				if (randomChoice < 50)
				{
					WaitingTimeBetwenAction();
				}
				else
				{
					behaviorValues.timeBehavior = 0;
					maxTimeAction = GenerateRandomFloat(100, 300);
					behaviorValues.isActionEnded = false;
					PlaceToMoveLocation = GetPlacePosition();
				}
			}
		}
		//WAITING
		else if (CurrentBehaviorsState == UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::WaitingNextAction)
		{
			if (waitingTime > 0)
			{
				waitingTime--;
			}
			else
				ChooseNextAction();
		}
	}

}

void AEnemies_Behaviors::SendMessageManager()
{
	//UE_LOG(LogTemp, Error, TEXT(" ------------------------ sendMessages ------------------------ "));
}
/////////////////////////// BASE BEHAVIOURS ///////////////////////////
void AEnemies_Behaviors::WaitingTimeBetwenAction()
{
	if (CurrentBehaviorsState != UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::IsInterrupted && 
		CurrentBehaviorsState != UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::Dead && 
		CurrentActionState != UStates_EnemiesActions::EStates_EnemiesActions::Dead)
	{
		StopAllActions();
		isIdle = true;
		SetActionState(UStates_EnemiesActions::EStates_EnemiesActions::Idle, 0.0f);

		waitingTime = GenerateRandomFloat(50, 100);

		SetBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::WaitingNextAction, 0.0f);
		behaviorValues.timeBehavior = 0;
		behaviorValues.isActionEnded = false;
	}
}
void AEnemies_Behaviors::ChooseNextAction()
{
	if (CurrentBehaviorsState != UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::IsInterrupted && ListBehaviors.Num() > 0 &&
		CurrentBehaviorsState != UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::Dead &&
		CurrentActionState != UStates_EnemiesActions::EStates_EnemiesActions::Dead)
	{
		int randomChoice = GenerateRandomInt(0, ListBehaviors.Num());
		//CHASING
		if (ListBehaviors[randomChoice] == "Chasing")
		{
			UE_LOG(LogTemp, Error, TEXT(" ChasingPlayer "));
			SetBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::ChasingPlayer, 0.0f);
		}
		//ATTACK
		if (ListBehaviors[randomChoice] == "Attack")
		{
			UE_LOG(LogTemp, Error, TEXT(" AttackPlayer "));
			SetBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::AttackPlayer, 0.0f);
		}
		//TURNING
		if (ListBehaviors[randomChoice] == "TurningAround")
		{
			UE_LOG(LogTemp, Error, TEXT(" TurnAroundPlayer "));
			maxTimeAction = GenerateRandomFloat(100, 300);
			distanceTurnPlayer = GenerateRandomInt(3, 8);
			int randomInt = GenerateRandomInt(0, 100);
			if (randomInt < 50)
				directiontoTurn = 1;
			else
				directiontoTurn = -1;
			SetBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::TurnAroundPlayer, 0.0f);
		}
		//EVALUATE
		if (ListBehaviors[randomChoice] == "Evaluate")
		{
			UE_LOG(LogTemp, Error, TEXT(" EvaluatePlayer "));
			PlaceToMoveLocation = GetPlacePosition();
			maxTimeAction = GenerateRandomFloat(100, 300);
			SetBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::EvaluatePlayer, 0.0f);
		}
		/*
			SetBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::ChasingPlayer, 0.0f);
		*/
	}
	
}


void AEnemies_Behaviors::MoveToPlayer(float distanceMaxMultiple, UStates_EnemiesActions::EStates_EnemiesActions state)
{
	if (PlayerCharacter)
	{
		float playerDistance = GetPlayerDistance();
		if (playerDistance > (distanceMaxMultiple * distanceToStopToPlayer))
		{
			SetActionState(state, 0.0f);
			FVector PlayerLocation = GetPlayerPosition();
			Moving(PlayerLocation);
			Turning(PlayerLocation);
		}
		else
		{
			behaviorValues.isActionEnded = true;
		}
		behaviorValues.timeBehavior++;
	}
}
void AEnemies_Behaviors::MoveToPlace(UStates_EnemiesActions::EStates_EnemiesActions state)
{
	if (PlayerCharacter)
	{
		float placeDistance = GetPlaceDistance(PlaceToMoveLocation);
		if (placeDistance > distanceToStopToPlayer)
		{
			SetActionState(state, 0.0f);

			FVector PlayerLocation = GetPlayerPosition();

			Moving(PlaceToMoveLocation);
			Turning(PlayerLocation);

			behaviorValues.timeBehavior++;
			if (maxTimeAction < behaviorValues.timeBehavior)
				behaviorValues.isActionEnded = true;
		}
		else
		{
			behaviorValues.isActionEnded = true;
		}
	}
}

void AEnemies_Behaviors::TurningAroundPlayer(float distanceMaxMultiple, UStates_EnemiesActions::EStates_EnemiesActions state)
{
	if (PlayerCharacter)
	{
		float playerDistance = GetPlayerDistance();
		FVector PlayerLocation = GetPlayerPosition();

		float Radius = distanceMaxMultiple * distanceToStopToPlayer;
		float AngularSpeed = 1.0f * directiontoTurn;
	
		float TimeElapsed = GetWorld()->GetTimeSeconds();

		float X = Radius * FMath::Cos(AngularSpeed * TimeElapsed);
		float Y = Radius * FMath::Sin(AngularSpeed * TimeElapsed);

		FVector EnemyNextPosition = PlayerLocation + FVector(X, Y, 0.0f);
		FVector InterpolatedLocation = FMath::VInterpTo(GetActorLocation(), EnemyNextPosition, GetWorld()->GetTimeSeconds(), 100.0f);

		SetActionState(state, 0.0f);
		Moving(InterpolatedLocation);
		Turning(PlayerLocation);

		behaviorValues.timeBehavior++;
		if(maxTimeAction < behaviorValues.timeBehavior)
			behaviorValues.isActionEnded = true;

	}
}


void AEnemies_Behaviors::AttackPlayer()
{
	if (isAttackStarted == false)
	{
		StopAllActions();

		isAttackStarted = true;
		behaviorValues.timeBehavior = 0;

		int randomChoice = GenerateRandomInt(1, 100);
		if (randomChoice < 50)
			StartAttack(false);
		else
			StartAttack(true);
	}
	Attack(behaviorValues.timeBehavior);
	behaviorValues.timeBehavior++;
}
void AEnemies_Behaviors::NextAttack()
{
	Super::NextAttack();
	behaviorValues.timeBehavior = 0;
}
void AEnemies_Behaviors::EndAttack()
{
	Super::EndAttack();
	behaviorValues.isActionEnded = true;
}


///////////////////////////////////////////////////////////////////////


/////////////////////////// REACTION BEHAVIOURS ///////////////////////////
void AEnemies_Behaviors::ReactionToPlayer()
{
	if (CurrentBehaviorsState != UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::Dead)
	{
		float playerDistance = GetPlayerDistance();

		if (CurrentPlayerState == UStates_PlayerF::EStates_PlayerF::Attack && playerDistance < (distanceToStopToPlayer * 2.5f))
		{
			int randomChoice = GenerateRandomInt(1, 100);
			if (randomChoice < 50 && ListReactionsBehaviors.Num() > 0)
			{
				StopAllActions();

				behaviorValues.timeBehavior = 0;
				behaviorValues.isActionEnded = false;

				float setTimeLag = GenerateRandomFloat(timeLagReactionMin, timeLagReactionMax);
				UE_LOG(LogTemp, Warning, TEXT(" setTimeLag = %f"), setTimeLag);

				FTimerHandle TimerHandle;
				GetWorldTimerManager().SetTimer(TimerHandle, [this]()
					{
						ReactionToAttacks();
					}, setTimeLag, false);

			}
		}
	}
}

void AEnemies_Behaviors::ReactionToAttacks()
{
	int RandomInt = GenerateRandomInt(0, ListReactionsBehaviors.Num());
	if (ListReactionsBehaviors[RandomInt] == "Dodge" && canDodge)
	{
		UE_LOG(LogTemp, Warning, TEXT(" ENEMY DODGE"));
		randomIntChoice = GenerateRandomInt(1, 90);
		canBeHit = false;
		SetBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::DodgeAttack, 0.0f);
	}
	else if (ListReactionsBehaviors[RandomInt] == "Counter")
	{
		UE_LOG(LogTemp, Warning, TEXT(" ENEMY COUNTER"));
		canCounter = true;
		SetBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::CounterAttack, 0.0f);
		SetActionState(UStates_EnemiesActions::EStates_EnemiesActions::CounterPose, 0.0f);
	}
}
void AEnemies_Behaviors::DodgeAttack()
{
	FVector PlayerLocation = GetPlayerPosition();
	Turning(PlayerLocation);

	const FVector RightVector = GetActorRightVector();
	const FVector ForwardVector = GetActorForwardVector();
	SetActionState(UStates_EnemiesActions::EStates_EnemiesActions::Dash, 0.0f);
	////RIGHT
	if (randomIntChoice <= 30)
	{
		behaviorValues.isActionEnded = ActionDash(RightVector, behaviorValues.timeBehavior);
	}
	////LEFT
	else if (randomIntChoice <= 60 && randomIntChoice > 30)
	{
		behaviorValues.isActionEnded = ActionDash(-RightVector, behaviorValues.timeBehavior);
	}
	////BACK
	else
	{
		behaviorValues.isActionEnded = ActionDash(-ForwardVector, behaviorValues.timeBehavior);
	}

	behaviorValues.timeBehavior++;
}
void AEnemies_Behaviors::CounterAttack()
{
	if (CurrentActionState == UStates_EnemiesActions::EStates_EnemiesActions::CounterPose && behaviorValues.isActionEnded == false)
	{
		behaviorValues.timeBehavior++;
		behaviorValues.isActionEnded = CounterPose(behaviorValues.timeBehavior);
	}
	if (CurrentActionState == UStates_EnemiesActions::EStates_EnemiesActions::Counter && behaviorValues.isActionEnded == false)
	{
		behaviorValues.timeBehavior++;
		behaviorValues.isActionEnded = Counter(behaviorValues.timeBehavior);
	}
}
///////////////////////////////////////////////////////////////////////

/////////////////////////// DELEGATE ///////////////////////////
void AEnemies_Behaviors::StopAllActions() 
{ 
	if(CurrentBehaviorsState == UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::IsInterrupted, 0.0f)
		waitingTime = 100; 
}
void AEnemies_Behaviors::NewAction()
{ 
	behaviorValues.timeBehavior = 0;
	behaviorValues.isActionEnded = false;
}