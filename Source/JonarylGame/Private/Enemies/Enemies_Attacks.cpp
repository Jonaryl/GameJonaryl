// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemies_Attacks.h"


void AEnemies_Attacks::BeginPlay()
{
	Super::BeginPlay();

	isAttackStarted = false;
    canBeHit = true;

    //// ATTACK LIST
    TInlineComponentArray<UActorComponent*> ComponentList;
    GetComponents(ComponentList);
    for (UActorComponent* Component : ComponentList)
    {
        UComponent_Enemies_Attacks* AttackComponent = Cast<UComponent_Enemies_Attacks>(Component);
        if (AttackComponent)
        {
            //// ATTACK NORMAL
            if(AttackComponent->GetisCombo() == false)
                attackList.Add(AttackComponent);
            //// ATTACK COMBO
            else
            {
                switch (AttackComponent->GetcomboID())
                {
                    case 0:
                        comboA.Add(AttackComponent);
                    break;
                    case 1:
                        comboB.Add(AttackComponent);
                    break;
                    case 2:
                        comboC.Add(AttackComponent);
                    break;
                    case 3:
                        comboD.Add(AttackComponent);
                    break;
                    case 4:
                        comboE.Add(AttackComponent);
                    break;
                }
            }
        }
    }
    attackList.Sort([](UComponent_Enemies_Attacks& A, UComponent_Enemies_Attacks& B)
        {
            return A.GetattackID() < B.GetattackID();
        });
    if (!comboA.IsEmpty())
    {
        comboA.Sort([](UComponent_Enemies_Attacks& A, UComponent_Enemies_Attacks& B)
        {
            return A.GetattackID() < B.GetattackID();
        });
        numberOfCombo = 0;
    }
    if (!comboB.IsEmpty())
    {
        comboB.Sort([](UComponent_Enemies_Attacks& A, UComponent_Enemies_Attacks& B)
        {
            return A.GetattackID() < B.GetattackID();
        });
        numberOfCombo++;
    }
    if (!comboC.IsEmpty())
    {
        comboC.Sort([](UComponent_Enemies_Attacks& A, UComponent_Enemies_Attacks& B)
        {
            return A.GetattackID() < B.GetattackID();
        });
        numberOfCombo++;
    }
    if (!comboD.IsEmpty())
    {
        comboD.Sort([](UComponent_Enemies_Attacks& A, UComponent_Enemies_Attacks& B)
            {
                return A.GetattackID() < B.GetattackID();
            });
        numberOfCombo++;
    }
    if (!comboE.IsEmpty())
    {
        comboE.Sort([](UComponent_Enemies_Attacks& A, UComponent_Enemies_Attacks& B)
        {
            return A.GetattackID() < B.GetattackID();
        });
        numberOfCombo++;
    }
}
void AEnemies_Attacks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if (HitCooldown >= 0)
    {
        HitCooldown--;        
        //UE_LOG(LogTemp, Log, TEXT(" HitCooldown = %f"), HitCooldown);
        if (HitCooldown == 0)
        {
            isSlowDownTake = false;
            canDodge = true;
            ModifyDmgBlend(0.0f, 0.0f, 0.0f);
        }
    }

    ///REGEN ARMOR
    if (regenArmorCooldown >= 0)
    {
        regenArmorCooldown--;
        if (regenArmorCooldown == 0)
        {
            Current_Armor = Max_Armor;
            //UE_LOG(LogTemp, Error, TEXT(" REGEN ARMOR "));
        }
    }
}

/////////////////////////// ATTACK ///////////////////////////
void AEnemies_Attacks::StartAttack(bool isCombo)
{
    //UE_LOG(LogTemp, Error, TEXT("StartAttack"));
    isCounterTake = false;
    currentAttacklist.Empty();
    isAttackCombo = isCombo;
    ///COMBO ATTACK
    if (isAttackCombo)
    {
        int RandomInt = GenerateRandomInt(0, numberOfCombo);
        switch (RandomInt)
        {
        case 0:
            for (UComponent_Enemies_Attacks* Component : comboA)
            {
                //UE_LOG(LogTemp, Error, TEXT(" Component %d"), Component->GetattackID());
                currentAttacklist.Add(Component);
            }
            break;
        case 1:
            for (UComponent_Enemies_Attacks* Component : comboB)
            {
                //UE_LOG(LogTemp, Error, TEXT(" Component %d"), Component->GetattackID());
                currentAttacklist.Add(Component);
            }
            break;
        case 2:
            for (UComponent_Enemies_Attacks* Component : comboC)
            {
                //UE_LOG(LogTemp, Error, TEXT(" Component %d"), Component->GetattackID());
                currentAttacklist.Add(Component);
            }
            break;
        case 3:
            for (UComponent_Enemies_Attacks* Component : comboD)
            {
                //UE_LOG(LogTemp, Error, TEXT(" Component %d"), Component->GetattackID());
                currentAttacklist.Add(Component);
            }
            break;
        case 4:
            for (UComponent_Enemies_Attacks* Component : comboE)
            {
                //UE_LOG(LogTemp, Error, TEXT(" Component %d"), Component->GetattackID());
                currentAttacklist.Add(Component);
            }
            break;
        }
    }
    ///SIMPLE ATTACK
    else
    {

        for (UComponent_Enemies_Attacks* Component : attackList)
        {
            currentAttacklist.Add(Component);
        }
        currentHitCombo = GenerateRandomInt(0, (currentAttacklist.Num() - 1));
    }
    if (!currentAttacklist.IsEmpty())
    {
        if (currentHitCombo >= 0 && currentHitCombo < currentAttacklist.Num() && currentAttacklist[currentHitCombo])
        {
            attackInstance = currentAttacklist[currentHitCombo];
            if (attackInstance)
            {
                FStruct_CharacterStats enemyStats;
                enemyStats.Health = Current_Health;
                enemyStats.Attack = Current_Attack;
                enemyStats.Defense = Current_Defense;
                enemyStats.MagicAttack = Current_MagicAttack;
                enemyStats.MagicDefense = Current_MagicDefense;

                attackInstance->StartAttack(enemyStats);
            }
        }
    }
}
void AEnemies_Attacks::Attack(int timeCurrentAttack)
{
    if (!currentAttacklist.IsEmpty())
    {
        if (currentHitCombo >= 0 && currentHitCombo < currentAttacklist.Num() && currentAttacklist[currentHitCombo])
        {
            attackInstance = currentAttacklist[currentHitCombo];
            if (attackInstance)
            {
                SetActionState(EStates_EnemiesActions::Attack, 0.0f);
                attackInstance->Attack(timeCurrentAttack);
                if (timeCurrentAttack < 5)
                {
                    if (PlayerCharacter)
                    {
                        FVector PlayerLocation = GetPlayerPosition();
                        Turning(PlayerLocation, 1.0f);
                    }
                }
                else if (timeCurrentAttack > 5 && timeCurrentAttack < (attackInstance->GettimeNextAttackCombo() - 8))
                {
                    if (PlayerCharacter)
                    {
                        FVector PlayerLocation = GetPlayerPosition();
                        Turning(PlayerLocation, 0.1f);
                    }
                }
                if (currentHitCombo == whishAttackToDebug)
                {
                    //UE_LOG(LogTemp, Warning, TEXT(" ENEMY timeCurrentAttack = %d"), timeCurrentAttack);
                }
                // ATTACK 
                if (timeCurrentAttack == attackInstance->GettimeAttack())
                {
                    /*
                    UE_LOG(LogTemp, Warning, TEXT(" ATTACK  %d"), attackInstance->GetattackID());
                    UE_LOG(LogTemp, Warning, TEXT(" combo  %d"), attackInstance->GetcomboID());
                    */
                    ModifyDmgBlend(0.0f, 0.0f, 0.0f);
                }
                // RESUME COMBO 
                if (timeCurrentAttack == attackInstance->GettimeNextAttackCombo())
                {
                    /*
                    UE_LOG(LogTemp, Error, TEXT(" RESUME COMBO "));
                    */
                    if (isAttackCombo && currentHitCombo < (currentAttacklist.Num() -1))
                        NextAttack();
                }
                // STOP ANIM 
                if (timeCurrentAttack == attackInstance->GettimeStopAnim())
                {
                    //UE_LOG(LogTemp, Warning, TEXT(" STOP ANIM  "));
                    EndAttack();
                }
            }
        }
    }
}
void AEnemies_Attacks::NextAttack()
{
    isCounterTake = false;
    currentHitCombo++;
    attackInstance = currentAttacklist[currentHitCombo];
    if (attackInstance)
    {
        FStruct_CharacterStats enemyStats;
        enemyStats.Health = Current_Health;
        enemyStats.Attack = Current_Attack;
        enemyStats.Defense = Current_Defense;
        enemyStats.MagicAttack = Current_MagicAttack;
        enemyStats.MagicDefense = Current_MagicDefense;

        attackInstance->StartAttack(enemyStats);
    }
}
void AEnemies_Attacks::EndAttack()
{
    isAttackStarted = false;
    currentHitCombo = 0;
}

void AEnemies_Attacks::AdvertAttack()
{
    if (advertAttackParticule)
    {
        AActor* AdvertAttackInstance = GetWorld()->SpawnActor<AActor>(advertAttackParticule, GetActorLocation(), GetActorRotation());
    }
}

void AEnemies_Attacks::LaunchParticle()
{
    attackInstance->LaunchParticle();
    //UE_LOG(LogTemp, Warning, TEXT(" ENEMY LaunchParticle"));
}
void AEnemies_Attacks::SpawnParticleCounter(AActor* Player)
{
    if (CounterParticle)
    {
        AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(CounterParticle, GetActorLocation(), GetActorRotation());

        IParticle_Enemies_I* AttackInterface = Cast<IParticle_Enemies_I>(AttackInstance);

        if (AttackInterface)
        {
            AttackInterface->Execute_IsCountered(AttackInstance, Player);
        }
    }
}
void AEnemies_Attacks::EnableDamage()
{
    attackInstance->EnableDamage();
    //UE_LOG(LogTemp, Warning, TEXT(" ENEMY EnableDamage"));
}

/////////////////////////// DAMAGE ///////////////////////////
void AEnemies_Attacks::ModifyDmgBlend(float alpha, float alphaR, float alphaL)
{
    DmgBlendAlpha = alpha;
    DmgBlendR = alphaR;
    DmgBlendL = alphaL;
}
void AEnemies_Attacks::DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, float ArmorDamage, int damageId)
{
    if (canBeHit && lastDamageID != damageId)
    {
        lastDamageID = damageId;
        HitCooldown = 20;
        // COUNTER
        if (CurrentActionState == EStates_EnemiesActions::CounterPose && canCounter == true)
        {
            UE_LOG(LogTemp, Error, TEXT(" ENEMY COUNTER"));                
            
            NewAction();

            isCounterPose = false;
            isCounter = true;
            canCounter = true;

            SetBehaviorState(EStates_EnemiesBehaviors::IsInterrupted, 0.0f);
            SetBehaviorState(EStates_EnemiesBehaviors::CounterAttacking, 0.0f);
            SetActionState(EStates_EnemiesActions::Counter, 0.0f);

            if (PlayerCharacter)
            {
                SpawnParticleCounter(PlayerCharacter);
            }
            /*counterNumber++;
            if (counterNumber == 4)
                counterNumber = 1;*/
        }
        // DAMAGE
        else if(canCounter == false)
        {
            Current_Health -= damage;

            if (CurrentActionState == EStates_EnemiesActions::CounterPose
                || CurrentActionState == EStates_EnemiesActions::Counter)
            {
                SetBehaviorState(EStates_EnemiesBehaviors::IsInterrupted, 0.0f);
                StopAllActions();
            }

            if (CurrentActionState != EStates_EnemiesActions::Damage)
                Current_Armor -= ArmorDamage;

            UE_LOG(LogTemp, Error, TEXT("ENEMY DAMAGE TAKE"));
            /*
            UE_LOG(LogTemp, Log, TEXT(" damage  %d"), damage);
            UE_LOG(LogTemp, Log, TEXT(" ArmorDamage  %f"), ArmorDamage);

            UE_LOG(LogTemp, Log, TEXT(" Current_Health  %f"), Current_Health);
            UE_LOG(LogTemp, Log, TEXT(" Current_Armor  %f"), Current_Armor);
            */

            isRightAttackHit = isRightDamage;
            hitCountDamageAnimation++;
            if (hitCountDamageAnimation == 4)
                hitCountDamageAnimation = 1;

            canDodge = false;

            if (Current_Armor <= 0 || isCutFromDamage)
            {
                SetBehaviorState(EStates_EnemiesBehaviors::IsInterrupted, 0.0f);
                SetActionState(EStates_EnemiesActions::Damage, 0.0f);

                StopAllActions();

                isDamaged = true;
                currentDamagedCooldown = 30.0f;
                if (regenArmorCooldown <= 0)
                    regenArmorCooldown = maxDamagedCooldown;
            }
            else
            {
                if (CurrentActionState != EStates_EnemiesActions::Attack)
                {
                    if (isRightDamage)
                        ModifyDmgBlend(0.7f, 1.0f, 0.0f);
                    else
                        ModifyDmgBlend(0.7f, 0.0f, 1.0f);
                }
            }

            if (Current_Health <= 0)
            {
                canBeHit = false;
                isEnemyDead = true;
                StopAllActions();
                SetBehaviorState(EStates_EnemiesBehaviors::IsInterrupted, 0.0f);
                SetActionState(EStates_EnemiesActions::Dead, 0.0f);

                UCapsuleComponent* CapsuleCollisionEnemy = AEnemies_Move::FindComponentByClass<UCapsuleComponent>();
                if (CapsuleCollisionEnemy)
                    CapsuleCollisionEnemy->SetCollisionEnabled(ECollisionEnabled::NoCollision);
                if(CollisionEnemy)
                    CollisionEnemy->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            }
        }
    }
}
void AEnemies_Attacks::CounterTake()
{
    isCounterTake = true;
}

void AEnemies_Attacks::EndSlowMode()
{
    isSlow = false;
    this->CustomTimeDilation = 1.0f;
    slowMotionCountDown = 0;
    HitCooldown = 60;
}
void AEnemies_Attacks::ActivateSlowMode()
{
    isSlow = true;
    this->CustomTimeDilation = 0.01f;
    slowMotionCountDown = 800;
}

void AEnemies_Attacks::SlowDownTake()
{
    if (isSlowDownTake == false)
    {
        isSlowDownTake = true;
        //isDamaged = true;
        SetBehaviorState(EStates_EnemiesBehaviors::IsInterrupted, 0.0f);
        SetActionState(EStates_EnemiesActions::Slow, 0.0f);

        FTimerHandle TimerHandle;
        GetWorldTimerManager().SetTimer(TimerHandle, [this]()
            {
                ActivateSlowMode();
            }, 0.1f, false);
    }
}

bool AEnemies_Attacks::GetisSlowDownTake()
{
    return isSlowDownTake;
}

/////////////////////////// COUNTER ///////////////////////////
bool AEnemies_Attacks::CounterPose(int actionCounterPoseTurn)
{
    bool isActionEnded = false;
    if (actionCounterPoseTurn == timeStopCounterPose)
    {
        canCounter = false;
    }
    if (actionCounterPoseTurn == timeStopAnimCounterPose)
    {
        isCounterPose = false;
        isActionEnded = true;
    }
    return isActionEnded;
}
bool AEnemies_Attacks::Counter(int actionCounterTurn)
{
    bool isActionEnded = false;
    if (actionCounterTurn == timeStopCounter)
    {
        canCounter = false;
    }
    if (actionCounterTurn == timeStopAnimCounterPose)
    {
        isCounter = false;
        isActionEnded = true;
    }
    return isActionEnded;
}

