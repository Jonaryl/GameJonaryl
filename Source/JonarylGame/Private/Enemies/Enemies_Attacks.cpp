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
    // DAMAGE
    if (CurrentActionState == UStates_EnemiesActions::EStates_EnemiesActions::Damage && damagedCooldown >= 0)
    {
        damagedCooldown--;
        if (damagedCooldown == 0)
        {
            Current_Armor = Max_Armor;
        }
    }
}

/////////////////////////// ATTACK ///////////////////////////
void AEnemies_Attacks::StartAttack(bool isCombo)
{
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
                UE_LOG(LogTemp, Error, TEXT(" Component %d"), Component->GetattackID());
                currentAttacklist.Add(Component);
            }
            break;
        case 1:
            for (UComponent_Enemies_Attacks* Component : comboB)
            {
                UE_LOG(LogTemp, Error, TEXT(" Component %d"), Component->GetattackID());
                currentAttacklist.Add(Component);
            }
            break;
        case 2:
            for (UComponent_Enemies_Attacks* Component : comboC)
            {
                UE_LOG(LogTemp, Error, TEXT(" Component %d"), Component->GetattackID());
                currentAttacklist.Add(Component);
            }
            break;
        case 3:
            for (UComponent_Enemies_Attacks* Component : comboD)
            {
                UE_LOG(LogTemp, Error, TEXT(" Component %d"), Component->GetattackID());
                currentAttacklist.Add(Component);
            }
            break;
        case 4:
            for (UComponent_Enemies_Attacks* Component : comboE)
            {
                UE_LOG(LogTemp, Error, TEXT(" Component %d"), Component->GetattackID());
                currentAttacklist.Add(Component);
            }
            break;
        }
    }
    ///SIMPLE ATTACK
    else
    {
        UE_LOG(LogTemp, Error, TEXT(" SIMPLE ATTACK"));

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
            UComponent_Enemies_Attacks* attackInstance = currentAttacklist[currentHitCombo];
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
            UComponent_Enemies_Attacks* attackInstance = currentAttacklist[currentHitCombo];
            if (attackInstance)
            {
                SetActionState(UStates_EnemiesActions::EStates_EnemiesActions::Attack, 0.0f);
                attackInstance->Attack(timeCurrentAttack);
                if (timeCurrentAttack < 5)
                {
                    if (PlayerCharacter)
                    {
                        FVector PlayerLocation = GetPlayerPosition();
                        Turning(PlayerLocation);
                    }
                }
                // ATTACK 
                if (timeCurrentAttack == attackInstance->GettimeAttack())
                {
                    UE_LOG(LogTemp, Warning, TEXT(" ATTACK  %d"), attackInstance->GetattackID());
                    UE_LOG(LogTemp, Warning, TEXT(" combo  %d"), attackInstance->GetcomboID());
                }
                // RESUME COMBO 
                if (timeCurrentAttack == attackInstance->GettimeNextAttackCombo())
                {
                    UE_LOG(LogTemp, Error, TEXT(" RESUME COMBO "));
                    if (isAttackCombo && currentHitCombo < (currentAttacklist.Num() -1))
                        NextAttack();
                }
                // STOP ANIM 
                if (timeCurrentAttack == attackInstance->GettimeStopAnim())
                {
                    UE_LOG(LogTemp, Warning, TEXT(" STOP ANIM  "));
                    EndAttack();
                }
            }
        }
    }
}
void AEnemies_Attacks::NextAttack()
{
    currentHitCombo++;
    UComponent_Enemies_Attacks* attackInstance = currentAttacklist[currentHitCombo];
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


/////////////////////////// DAMAGE ///////////////////////////
void AEnemies_Attacks::ModifyDmgBlend(float alpha, float alphaR, float alphaL)
{
    DmgBlendAlpha = alpha;
    DmgBlendR = alphaR;
    DmgBlendL = alphaL;
}
void AEnemies_Attacks::DamageTake(int damage, bool isRightDamage, bool isCutFromDamage, float ArmorDamage)
{
    if (canBeHit)
    {
        // DAMAGE
        if (CurrentActionState != UStates_EnemiesActions::EStates_EnemiesActions::CounterPose)
        {
            Current_Health -= damage;

            if (CurrentActionState != UStates_EnemiesActions::EStates_EnemiesActions::Damage)
                Current_Armor -= ArmorDamage;

            if (Current_Armor <= 0 || isCutFromDamage)
            {
                SetBehaviorState(UStates_EnemiesBehaviors::EStates_EnemiesBehaviors::IsInterrupted, 0.0f);
                SetActionState(UStates_EnemiesActions::EStates_EnemiesActions::Damage, 0.0f);
                damagedCooldown = 10;
            }
            else
            {
                if (isRightDamage)
                    ModifyDmgBlend(0.5f, 1.0f, 0.0f);
                else
                    ModifyDmgBlend(0.5f, 0.0f, 1.0f);
            }
        }
        // COUNTER
        else
        {
            //isCounterPose = false;
            //isCounter = true;

            SetActionState(UStates_EnemiesActions::EStates_EnemiesActions::Counter, 0.0f);

            /*counterNumber++;
            if (counterNumber == 4)
                counterNumber = 1;*/
        }
    }
}
