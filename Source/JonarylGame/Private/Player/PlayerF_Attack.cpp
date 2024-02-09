// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerF_Attack.h"


/////////////////////////// BASE METHOD ///////////////////////////
void APlayerF_Attack::BeginPlay()
{
    Super::BeginPlay();

    canBeHit = true;
    canAttack = true;
    canCounterPose = true;
    canCounter = false;
    canAttackSpe = false;
    onCombo = false;
    currentHitCombo = -1;
    counterPoseNumber = 0;
    counterNumber = 0;
    damageAnimNumber = 0;

    //// ATTACK LIST
    //TArray<UActorComponent*> ComponentList = GetComponentsByClass(UComponent_PlayerF_Attacks::StaticClass());
    TInlineComponentArray<UActorComponent*> ComponentList;
    GetComponents(ComponentList);
    for (UActorComponent* Component : ComponentList)
    {
        //// ATTACK SPECIAL
        if (Component->GetName() == "SpecialAttack")
        {
            SpecialAttack = Cast<UComponent_PlayerF_SpeAtk>(Component);
        }

        //// ATTACK LIST
        UComponent_PlayerF_Attacks* AttackComponent = Cast<UComponent_PlayerF_Attacks>(Component);
        if (AttackComponent)
        {
            attackList.Add(AttackComponent);
        }
    }
    attackList.Sort([](UComponent_PlayerF_Attacks& A, UComponent_PlayerF_Attacks& B)
        {
            return A.GetattackID() < B.GetattackID();
        });


    PostProcessSlow = FindComponentByClass<UPostProcessComponent>();
    if (PostProcessSlow)
        PostProcessSlowActivate(false);


    if (PlayerFightHUD)
    {
        PlayerFightHUD->SetHealth(Max_Health, Current_Health);
        PlayerFightHUD->SetClassPower(counterGaugeMax, currentCounterGauge);
    }
}

void APlayerF_Attack::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ATTACK
    if (CurrentState == UStates_PlayerF::EStates_PlayerF::Attack
        && !attackList.IsEmpty() && currentHitCombo != -1 && isAttacking)
    {
        if (currentHitCombo >= 0 && currentHitCombo < attackList.Num() && attackList[currentHitCombo])
        {
            UComponent_PlayerF_Attacks* attackInstance = attackList[currentHitCombo];
            if (attackInstance)
            {
                attackInstance->Attack();
                timeCurrentAttack = attackInstance->GettimeCurrentAttack();

                ///TURNING
                if (enemyTargetLock != nullptr)
                {
                    ActionMovingAndTurning(GetActorLocation(), timeCurrentAttack, 50000000000.0f, 10.0f);
                }
                else if (isMoveInput)
                {
                    ActionMovingAndTurning(GetActorLocation(), timeCurrentAttack, 50000000000.0f, 4.0f);
                }
                /*
                */
                if (timeCurrentAttack == 1)
                    UE_LOG(LogTemp, Warning, TEXT(" ATTACK ID = %d"), attackInstance->GetattackID());

                //DEBUG
                if (currentHitCombo == whishAttackToDebug)
                {
                    UE_LOG(LogTemp, Warning, TEXT(" timeCurrentAttack = %f"), timeCurrentAttack);
                }
                // ATTACK 
                if (timeCurrentAttack == attackInstance->GettimeAttack())
                {
                    //UE_LOG(LogTemp, Warning, TEXT(" ATTACK  "));

                }
                // RESUME COMBO 
                if (timeCurrentAttack == attackInstance->GettimeWhenCanContinueCombo())
                {
                    //UE_LOG(LogTemp, Error, TEXT(" RESUME COMBO "));
                    canAttack = true;
                }
                // CAN MOVE 
                if (timeCurrentAttack == attackInstance->GettimeWhenCanMove())
                {
                   // UE_LOG(LogTemp, Warning, TEXT(" CAN MOVE "));
                    canMove = true;
                }
                // STOP COMBO 
                if (timeCurrentAttack == attackInstance->GettimeWhenStopCombo())
                {
                    //UE_LOG(LogTemp, Warning, TEXT(" STOP COMBO  "));
                    onCombo = false;
                }
                // STOP ANIM 
                if (timeCurrentAttack == attackInstance->GettimeWhenStopAnim())
                {
                    //UE_LOG(LogTemp, Warning, TEXT(" STOP ANIM  "));
                    EndAttack();
                }
            }
        }
    }
    // COUNTER POSE
    if (CurrentState == UStates_PlayerF::EStates_PlayerF::CounterPose)
    {
        timeCounterPose++;
        //UE_LOG(LogTemp, Warning, TEXT(" timeCounterPose %f"), timeCounterPose);
        if (timeCounterPose == timeStartCounterPose)
        {
            //UE_LOG(LogTemp, Warning, TEXT("  Start CounterPose  %f"), timeCounterPose);
            canCounter = true;
        }
        if (timeCounterPose == timeStopCounterPose)
        {
            //UE_LOG(LogTemp, Warning, TEXT(" Stop CounterPose %f"), timeCounterPose);
            canCounter = false;
        }
        if (timeCounterPose == timeCanActionCounterPose)
        {
            //UE_LOG(LogTemp, Warning, TEXT(" Can Action CounterPose %f"), timeCounterPose);
            canAttack = true;
            canMove = true;
            canCounterPose = true;
        }
        if (timeCounterPose == timeStopAnimCounterPose)
        {
           //UE_LOG(LogTemp, Error, TEXT(" timeStopAnimCounterPose %f"), timeStopAnimCounterPose);
            //UE_LOG(LogTemp, Warning, TEXT(" Stop Anim CounterPose %f"), timeCounterPose);
            EndCounterPose();
        }

    }
    // COUNTER
    if (CurrentState == UStates_PlayerF::EStates_PlayerF::Counter)
    {
        timeCounter++;
        //UE_LOG(LogTemp, Log, TEXT(" timeCounter = %f"), timeCounter);
        if (timeCounter == (timeCanAttackSpe -1))
        {
            float TierCounterGauge = counterGaugeMax / 3;
            if (currentCounterGauge > TierCounterGauge)
                LaunchAtkSpeFlashParticle();
        }
        if (timeCounter == timeCanAttackSpe)
        {
            //UE_LOG(LogTemp, Warning, TEXT(" Can AttackSpe "));
            canAttackSpe = true;
        }
        if (timeCounter == timeStopCanAttackSpe)
        {
            //UE_LOG(LogTemp, Warning, TEXT(" Stop Can AttackSpe "));
            canAttackSpe = false;
        }
        if (timeCounter == timeCanActionCounter)
        {
            //UE_LOG(LogTemp, Warning, TEXT(" Can Action Counter "));
            canCounter = false;
            canAttack = true;
            canMove = true;
            canCounterPose = true;
        }
        if (timeCounter == timeStopAnimCounter)
        {
            //UE_LOG(LogTemp, Warning, TEXT(" Stop Anim Counter "));
            EndCounter();
        }
    }
    if (currentCounterGauge > 0 && isSuperMode == false)
    {
        currentCounterGauge = currentCounterGauge - 0.01f;
        if (PlayerFightHUD)
            PlayerFightHUD->SetClassPower(counterGaugeMax, currentCounterGauge);
    }
    // DAMAGE
    if (CurrentState == UStates_PlayerF::EStates_PlayerF::Damage)
    {
        damagedCooldown++;
        if (damagedCooldown == timeCanMoveDamage)
        {
            //UE_LOG(LogTemp, Error, TEXT(" DAMAGE CAN MOVE"));
            NeutralAction();
        }
        if (damagedCooldown == timeEndDamage)
        {
            //UE_LOG(LogTemp, Error, TEXT(" DAMAGE END"));
            EndAttack();
        }
    }


    //REGEN ARMOR
    if (regenArmorCooldown >= 0)
    {
        regenArmorCooldown--;
        if (regenArmorCooldown <= 0)
        {
            //UE_LOG(LogTemp, Error, TEXT(" REGEN ARMOR END"));
            Current_Armor = Max_Armor;
        }
    }
}

void APlayerF_Attack::NeutralAction() {}
void APlayerF_Attack::StopMovingAnim() {}
void APlayerF_Attack::EndPartialAction() {}

/////////////////////////// ATTACK ///////////////////////////
void APlayerF_Attack::EndAttack()
{
    isAttacking = false;
    isDamaged = false;
    if (isMoveInput)
    {
        SetCharacterState(UStates_PlayerF::EStates_PlayerF::Run, 0.0f);
        isMoving = true;
    }
    else
    {
        SetCharacterState(UStates_PlayerF::EStates_PlayerF::Idle, 0.0f);
        isIdle = true;
    }
    NeutralAction();
}

/////////////////////////// COUNTER ///////////////////////////
void APlayerF_Attack::EndCounterPose()
{
    isCounterPose = false;
    //UE_LOG(LogTemp, Error, TEXT(" false isCounterPose --- EndCounterPose "));
    if (isMoveInput)
    {
        SetCharacterState(UStates_PlayerF::EStates_PlayerF::Run, 0.0f);
        isMoving = true;
    }
    else
    {
        SetCharacterState(UStates_PlayerF::EStates_PlayerF::Idle, 0.0f);
        isIdle = true;
    }
}
void APlayerF_Attack::EndCounter()
{
    isCounter = false;
    if (isMoveInput)
    {
        SetCharacterState(UStates_PlayerF::EStates_PlayerF::Run, 0.0f);
        isMoving = true;
    }
    else
    {
        SetCharacterState(UStates_PlayerF::EStates_PlayerF::Idle, 0.0f);
        isIdle = true;
    }
}

void APlayerF_Attack::SpawnParticleCounter(bool isRightDamage, AActor* Enemy)
{
    if (CounterParticleL && CounterParticleR)
    {
        TSubclassOf<AActor> AttackClass;
        if (isRightDamage)
            AttackClass = CounterParticleR;
        else
            AttackClass = CounterParticleL;

        AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(AttackClass, GetActorLocation(), GetActorRotation());

        IParticle_PlayerF_I* AttackInterface = Cast<IParticle_PlayerF_I>(AttackInstance);

        if (AttackInterface)
        {
            AttackInterface->Execute_IsCountered(AttackInstance, Enemy);
        }
    }
}
void APlayerF_Attack::LaunchAtkSpeFlashParticle()
{
    if (CanAtkSpeFlashParticle)
    {
        AActor* AttackInstance = GetWorld()->SpawnActor<AActor>(CanAtkSpeFlashParticle, GetActorLocation(), GetActorRotation());

        IParticle_PlayerF_I* AttackInterface = Cast<IParticle_PlayerF_I>(AttackInstance);
    }
}

/////////////////////////// SPECIAL ///////////////////////////
void APlayerF_Attack::PostProcessSlowActivate(bool isActivate) 
{
    //UE_LOG(LogTemp, Warning, TEXT("PostProcessSlowActivate isActivate = %s"), isActivate ? TEXT("True") : TEXT("False"));
    PostProcessSlow->bEnabled = isActivate;
}
void APlayerF_Attack::SuperModeActivate()
{
    if (isSuperMode == true)
    {
        isSuperMode = false;
        SetCharacterState(UStates_PlayerF::EStates_PlayerF::Idle, 0.0f);
    }
    else
        isSuperMode = true;
}

/////////////////////////// DAMAGE ///////////////////////////
void APlayerF_Attack::DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, AActor* Enemy, float ArmorDamage, int damageId)
{
    if (canBeHit && lastDamageID != damageId)
    {
        lastDamageID = damageId;
        // DAMAGE
        if (canCounter == false)
        {
            Current_Health -= damage;
            if (PlayerFightHUD)
                PlayerFightHUD->SetHealth(Max_Health, Current_Health);

            if(CurrentState != UStates_PlayerF::EStates_PlayerF::Damage)
                Current_Armor -= ArmorDamage;

            isDamageRight = isRightDamage;
            if (Current_Armor <= 0 || isCutFromDamage)
            {
                StopMovingAnim();
                EndAllActionAnim();

                canMove = false;
                canAttack = false;

                isDamaged = true;
                damageAnimNumber++;
                if (damageAnimNumber == 4)
                    damageAnimNumber = 1;

                //UE_LOG(LogTemp, Error, TEXT("------------   TRUE DAMAGE AVEC ANIM -------------"));

                regenArmorCooldown = 300;
                damagedCooldown = 0;

                SetCharacterState(UStates_PlayerF::EStates_PlayerF::Damage, 0.0f);
            }

            //UE_LOG(LogTemp, Error, TEXT("TAKE DAMAGE"));
            /*
            UE_LOG(LogTemp, Log, TEXT(" 222222222   ArmorDamage  %f"), ArmorDamage);

            UE_LOG(LogTemp, Log, TEXT(" 222222222   Current_Armor  %f"), Current_Armor);
            UE_LOG(LogTemp, Warning, TEXT(" isCutFromDamage = %s"), isCutFromDamage ? TEXT("True") : TEXT("False"));
            UE_LOG(LogTemp, Log, TEXT(" 222222222   damage  %d"), damage);
            UE_LOG(LogTemp, Log, TEXT(" 222222222   Current_Health  %f"), Current_Health);
            */
        }
        // COUNTER
        else
        {
            //UE_LOG(LogTemp, Error, TEXT("   COUNTER     "));
            StopMovingAnim();
            timeCounter = 0;
            currentCounterGauge += 10;
            
            isRightCounter = isRightDamage;
            isCounterPose = false;
            isCounter = true;

            SetCharacterState(UStates_PlayerF::EStates_PlayerF::Counter, 0.0f);

            counterNumber++;
            if (counterNumber == 4)
                counterNumber = 1;

            SpawnParticleCounter(isRightDamage, Enemy);
            TurningTo(Enemy->GetActorLocation(), 10.0f);

            if (PlayerFightHUD)
                PlayerFightHUD->SetClassPower(counterGaugeMax, currentCounterGauge);
        }
    }
}

/////////////////////////// INPUT ///////////////////////////
void APlayerF_Attack::ABtnAction()
{
    if (isSuperMode)
    {
        if (SpecialAttack)
            SpecialAttack->ABtnActionSpe();
    }
    else
        Super::ABtnAction();
}
void APlayerF_Attack::BBtnAction()
{
    Super::BBtnAction();
    //UE_LOG(LogTemp, Warning, TEXT(" BBtnAction  canCounterPose = %s"), canCounterPose ? TEXT("True") : TEXT("False"));
    if (isSuperMode)
    {
        if (SpecialAttack)
        {
            SpecialAttack->GetPlayer(this);
            if (enemyTargetLock)
                SpecialAttack->SetEnemyLocked(enemyTargetLock);
            SpecialAttack->BBtnActionSpe();
            float TierCounterGauge = counterGaugeMax / 3;
            currentCounterGauge -= TierCounterGauge;
            if (currentCounterGauge < 0)
                currentCounterGauge = 0;
        }
    }
    else
    {
        if (CurrentState == UStates_PlayerF::EStates_PlayerF::Run || CurrentState == UStates_PlayerF::EStates_PlayerF::Idle
            || CurrentState == UStates_PlayerF::EStates_PlayerF::Attack || CurrentState == UStates_PlayerF::EStates_PlayerF::Counter
            || CurrentState == UStates_PlayerF::EStates_PlayerF::Sprint || CurrentState == UStates_PlayerF::EStates_PlayerF::CounterPose
            )
        {
            if (canCounterPose)
            {
                StopMovingAnim();
                EndPartialAction();

                isCounterPose = true;
                canCounterPose = false;
                timeCounterPose = 0;
                SetCharacterState(UStates_PlayerF::EStates_PlayerF::CounterPose, 0.0f);

                counterPoseNumber++;
                if (counterPoseNumber == 4)
                    counterPoseNumber = 1;
            }
        }
    }
}
void APlayerF_Attack::XBtnAction()
{
    Super::XBtnAction();
    //UE_LOG(LogTemp, Warning, TEXT(" XBtnAction  canAttack = %s"), canAttack ? TEXT("True") : TEXT("False"));

    if (isSuperMode)
    {
        if (SpecialAttack)
        {
            SpecialAttack->GetPlayer(this);
            if (enemyTargetLock)
                SpecialAttack->SetEnemyLocked(enemyTargetLock);
            SpecialAttack->XBtnActionSpe();
            float TierCounterGauge = counterGaugeMax / 3;
            currentCounterGauge -= TierCounterGauge;
            if (currentCounterGauge < 0)
                currentCounterGauge = 0;
        }
    }
    else
    {
        if (CurrentState == UStates_PlayerF::EStates_PlayerF::Run || CurrentState == UStates_PlayerF::EStates_PlayerF::Idle
            || CurrentState == UStates_PlayerF::EStates_PlayerF::Sprint || CurrentState == UStates_PlayerF::EStates_PlayerF::Dash
            || CurrentState == UStates_PlayerF::EStates_PlayerF::Attack || CurrentState == UStates_PlayerF::EStates_PlayerF::Counter
            )
        {
            if (canAttack)
            {
                StopMovingAnim();
                EndPartialAction();

                SetCharacterState(UStates_PlayerF::EStates_PlayerF::ChangeAction, 0.0f);
                SetCharacterState(UStates_PlayerF::EStates_PlayerF::Attack, 0.0f);
                currentHitCombo++;
                if (!attackList.IsEmpty())
                {
                    if (currentHitCombo == attackList.Num() || onCombo == false)
                        currentHitCombo = 0;

                    onCombo = true;

                    if (currentHitCombo >= 0 && currentHitCombo < attackList.Num() && attackList[currentHitCombo])
                    {
                        UComponent_PlayerF_Attacks* attackInstance = attackList[currentHitCombo];
                        if (attackInstance)
                        {
                            FStruct_CharacterStats playerStats;
                            playerStats.Health = Current_Health;
                            playerStats.Attack = Current_Attack;
                            playerStats.Defense = Current_Defense;
                            playerStats.MagicAttack = Current_MagicAttack;
                            playerStats.MagicDefense = Current_MagicDefense;

                            attackInstance->StartAttack(this, playerStats);
                            timeCurrentAttack = attackInstance->GettimeCurrentAttack();

                            enemyTargetLock = PlayerFight_LockInstance->GetLastTarget();
                            attackInstance->SetEnemyLocked(enemyTargetLock);
                        }
                    }
                }
                // ANIM
                isAttacking = true;
                if (currentHitCombo == 0)
                {
                    AttackOneNumber++;
                    if (AttackOneNumber == 4)
                        AttackOneNumber = 1;
                }
                else
                    AttackOneNumber = 0;


                canAttack = false;
                //UE_LOG(LogTemp, Warning, TEXT(" currentHitCombo AFTER = %d"), currentHitCombo);
            }
        }
    }
}
void APlayerF_Attack::YBtnAction()
{
    Super::YBtnAction();
  
    if (isSuperMode)
    {
        if (SpecialAttack)
        {
            SpecialAttack->GetPlayer(this);
            SpecialAttack->YBtnActionSpe();
            float TierCounterGauge = counterGaugeMax / 3;
            currentCounterGauge -= TierCounterGauge;
            if (currentCounterGauge < 0)
                currentCounterGauge = 0;
        }
    }
    else
    {
        if (CurrentState == UStates_PlayerF::EStates_PlayerF::Counter && canAttackSpe 
            || CurrentState == UStates_PlayerF::EStates_PlayerF::Run || CurrentState == UStates_PlayerF::EStates_PlayerF::Idle)
        {
            canCounter = false;
            float TierCounterGauge = counterGaugeMax / 3;
            //UE_LOG(LogTemp, Error, TEXT(" TierCounterGauge = %f"), TierCounterGauge);
            if (currentCounterGauge > TierCounterGauge)
            {
                UE_LOG(LogTemp, Warning, TEXT(" Launch ATTACK SPE POSE "));
                if (SpecialAttack)
                {
                    SpecialAttack->GetPlayer(this);
                    if(enemyTargetLock)
                        SpecialAttack->SetEnemyLocked(enemyTargetLock);
                    if (CurrentState == UStates_PlayerF::EStates_PlayerF::Counter)
                        SpecialAttack->SpecialAttack(true);
                    else
                        SpecialAttack->SpecialAttack(false);
                }
            }
        }
    }
}



void APlayerF_Attack::DebugBtnAction()
{
    Super::DebugBtnAction();

    UE_LOG(LogTemp, Error, TEXT(" ATTACK "));
    UE_LOG(LogTemp, Warning, TEXT(" canCounterPose = %s"), canCounterPose ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" canCounterPose = %s"), canCounter ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" isCounterPose = %s"), isCounterPose ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" isCounterPose = %s"), isCounter ? TEXT("True") : TEXT("False"));

    UE_LOG(LogTemp, Warning, TEXT(" canAttack = %s"), canAttack ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" onCombo = %s"), onCombo ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" isAttacking = %s"), isAttacking ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Warning, TEXT(" currentHitCombo = %d"), currentHitCombo);
}