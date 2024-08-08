// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsSubsystem.h"

void UStatsSubsystem::InitializeSubsystem(FString InSaveSlotName)
{
    InitializeSavingSystem(InSaveSlotName, USG_StatsSlot::StaticClass());

    StatsSave = Cast<USG_StatsSlot>(LoadSlotData());
}


float UStatsSubsystem::GetBalance()
{
    StatsSave = Cast<USG_StatsSlot>(LoadSlotData());

    return StatsSave->Balance;
}

void UStatsSubsystem::GiveMoney(float Amount)
{
    StatsSave = Cast<USG_StatsSlot>(LoadSlotData());
    StatsSave->Balance += Amount;
    SaveSlotData(StatsSave);

    BalanceDispatcher.Broadcast(StatsSave->Balance);
}
