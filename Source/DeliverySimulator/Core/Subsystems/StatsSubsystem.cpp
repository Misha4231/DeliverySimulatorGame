// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsSubsystem.h"

void UStatsSubsystem::InitializeSubsystem()
{
    LoadDataFromSlot();

    
}

void UStatsSubsystem::LoadDataFromSlot()
{
    if (UGameplayStatics::DoesSaveGameExist(StatsSaveSlotName, 0)) {
        StatsSave = Cast<USG_StatsSlot>(UGameplayStatics::LoadGameFromSlot(StatsSaveSlotName, 0));
        
    } else {
        StatsSave = Cast<USG_StatsSlot>(UGameplayStatics::CreateSaveGameObject(USG_StatsSlot::StaticClass()));
        UGameplayStatics::SaveGameToSlot(StatsSave, StatsSaveSlotName, 0);
    }
}
void UStatsSubsystem::SaveDataToSlot(){
    if (UGameplayStatics::DoesSaveGameExist(StatsSaveSlotName, 0)) {
        UGameplayStatics::SaveGameToSlot(StatsSave, StatsSaveSlotName, 0);
    } else {
        StatsSave = Cast<USG_StatsSlot>(UGameplayStatics::CreateSaveGameObject(USG_StatsSlot::StaticClass()));
        UGameplayStatics::SaveGameToSlot(StatsSave, StatsSaveSlotName, 0);
    }
}

float UStatsSubsystem::GetBalance()
{
    LoadDataFromSlot();

    return StatsSave->Balance;
}

void UStatsSubsystem::GiveMoney(float Amount)
{
    LoadDataFromSlot();
    StatsSave->Balance += Amount;
    SaveDataToSlot();

    BalanceDispatcher.Broadcast(StatsSave->Balance);
}
