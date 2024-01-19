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

    //// ATTACK LIST
    //TArray<UActorComponent*> ComponentList = GetComponentsByClass(UComponent_PlayerF_Attacks::StaticClass());
    TInlineComponentArray<UActorComponent*> ComponentList;
    GetComponents(ComponentList);
    for (UActorComponent* Component : ComponentList)
    {
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
    for (UComponent_PlayerF_Attacks* Component : attackList)
    {
        UE_LOG(LogTemp, Warning, TEXT(" ya un truc timeAttack = %f"), Component->GettimeAttack());
    }

    //// ATTACK SPECIAL
    //SpecialAttack = NewObject<UComponent_PlayerF_SpeAtk>(this, UComponent_PlayerF_SpeAtk::StaticClass());
    SpecialAttack = FindComponentByClass<UComponent_PlayerF_SpeAtk>();
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


                if (isMoveInput)
                {
                    ActionMovingAndTurning(GetActorLocation(), timeCurrentAttack, 50000000000.0f, 4.0f);
                }

                if (timeCurrentAttack == 1)
                    UE_LOG(LogTemp, Warning, TEXT(" ATTACK ID = %d"), attackInstance->GetattackID());

                if (currentHitCombo == whishAttackToDebug)
                {
                    UE_LOG(LogTemp, Warning, TEXT(" timeCurrentAttack = %f"), timeCurrentAttack);
                }
                // ATTACK 
                if (timeCurrentAttack == attackInstance->GettimeAttack())
                {
                    UE_LOG(LogTemp, Warning, TEXT(" ATTACK  "));

                }
                // RESUME COMBO 
                if (timeCurrentAttack == attackInstance->GettimeWhenCanContinueCombo())
                {
                    UE_LOG(LogTemp, Error, TEXT(" RESUME COMBO "));
                    canAttack = true;
                }
                // CAN MOVE 
                if (timeCurrentAttack == attackInstance->GettimeWhenCanMove())
                {
                    UE_LOG(LogTemp, Warning, TEXT(" CAN MOVE "));
                    canMove = true;
                }
                // STOP COMBO 
                if (timeCurrentAttack == attackInstance->GettimeWhenStopCombo())
                {
                    UE_LOG(LogTemp, Warning, TEXT(" STOP COMBO  "));
                    onCombo = false;
                }
                // STOP ANIM 
                if (timeCurrentAttack == attackInstance->GettimeWhenStopAnim())
                {
                    UE_LOG(LogTemp, Warning, TEXT(" STOP ANIM  "));
                    EndAttack();
                }
            }
        }
    }
    // COUNTER POSE
    if (CurrentState == UStates_PlayerF::EStates_PlayerF::CounterPose)
    {
        timeCounterPose++;
        UE_LOG(LogTemp, Warning, TEXT(" timeCounterPose = %f"), timeCounterPose);
        if (timeCounterPose == timeStartCounterPose)
        {
            UE_LOG(LogTemp, Warning, TEXT("  Start CounterPose "));
            canCounter = true;
        }
        if (timeCounterPose == timeStopCounterPose)
        {
            UE_LOG(LogTemp, Warning, TEXT(" Stop CounterPose "));
            canCounter = false;
        }
        if (timeCounterPose == timeCanActionCounterPose)
        {
            UE_LOG(LogTemp, Warning, TEXT(" Can Action CounterPose "));
            canAttack = true;
            canMove = true;
            canCounterPose = true;
        }
        if (timeCounterPose == timeStopAnimCounterPose)
        {
            UE_LOG(LogTemp, Warning, TEXT(" Stop Anim CounterPose "));
            EndCounterPose();
        }

    }
    // COUNTER
    if (CurrentState == UStates_PlayerF::EStates_PlayerF::Counter)
    {
        timeCounter++;
        if (timeCanAttackSpe == timeStopAnimCounter)
        {
            UE_LOG(LogTemp, Warning, TEXT(" Can AttackSpe "));
            canAttackSpe = true;
        }
        if (timeStopCanAttackSpe == timeStopAnimCounter)
        {
            UE_LOG(LogTemp, Warning, TEXT(" Stop Can AttackSpe "));
            canAttackSpe = false;
        }
        if (timeCounter == timeCanActionCounter)
        {
            UE_LOG(LogTemp, Warning, TEXT(" Can Action Counter "));
            canAttack = true;
            canMove = true;
            canCounterPose = true;
        }
        if (timeCounterPose == timeStopAnimCounter)
        {
            UE_LOG(LogTemp, Warning, TEXT(" Stop Anim Counter "));
            EndCounter();
        }
    }
    if (currentCounterGauge > 0 && isSuperMode == false)
    {
        currentCounterGauge = currentCounterGauge - 0.01f;
        //if (PlayerFightHUD)
        //    PlayerFightHUD->SetClassPower(counterGaugeMax, currentCounterGauge);
    }
    // DAMAGE
    if (CurrentState == UStates_PlayerF::EStates_PlayerF::Damage && damagedCooldown >= 0)
    {
        damagedCooldown--;
        if (damagedCooldown == 0)
        {
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

/////////////////////////// SPECIAL ///////////////////////////
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
void APlayerF_Attack::DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, int damageCut, AActor* Enemy)
{
    if (canBeHit)
    {
        // DAMAGE
        if (canCounter == false)
        {
            Current_Health -= damage;

            if(CurrentState != UStates_PlayerF::EStates_PlayerF::Damage)
                Current_Armor -= damageCut;

            if (Current_Armor <= 0 || isCutFromDamage)
            {
                StopMovingAnim();
                EndAllActionAnim();

                isDamaged = true;

                SetCharacterState(UStates_PlayerF::EStates_PlayerF::Damage, 0.0f);
                damagedCooldown = 10;
            }
        }
        // COUNTER
        else
        {
            StopMovingAnim();
            timeCounter = 0;
            currentCounterGauge += 10;
            
            isCounterPose = false;
            isCounter = true;

            SetCharacterState(UStates_PlayerF::EStates_PlayerF::Counter, 0.0f);

            counterNumber++;
            if (counterNumber == 4)
                counterNumber = 1;
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
    UE_LOG(LogTemp, Warning, TEXT(" BBtnAction  canCounterPose = %s"), canCounterPose ? TEXT("True") : TEXT("False"));
    if (isSuperMode)
    {
        if (SpecialAttack)
        {
            SpecialAttack->GetPlayer(this);
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

                UE_LOG(LogTemp, Warning, TEXT(" BBtnAction  counterPoseNumber = %d"), counterPoseNumber );
            }
        }
    }
}
void APlayerF_Attack::XBtnAction()
{
    Super::XBtnAction();

    UE_LOG(LogTemp, Warning, TEXT(" XBtnAction  canAttack = %s"), canAttack ? TEXT("True") : TEXT("False"));

    if (isSuperMode)
    {
        if (SpecialAttack)
        {
            SpecialAttack->GetPlayer(this);
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
            || CurrentState == UStates_PlayerF::EStates_PlayerF::Attack
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
                UE_LOG(LogTemp, Warning, TEXT(" currentHitCombo AFTER = %d"), currentHitCombo);
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
        float TierCounterGauge = counterGaugeMax / 3;
        UE_LOG(LogTemp, Error, TEXT(" TierCounterGauge = %d"), TierCounterGauge);
        if (currentCounterGauge > TierCounterGauge || counterGaugeMax == 0)
        {
            UE_LOG(LogTemp, Warning, TEXT(" Launch ATTACK SPE POSE "));
            if (SpecialAttack)
                SpecialAttack->SpecialAttack();
        }
    }
    if (canAttackSpe)
    {
    }
}