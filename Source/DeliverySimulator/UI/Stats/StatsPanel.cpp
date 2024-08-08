// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsPanel.h"
#include "DeliverySimulator/Core/MainGameInstance.h"


void UStatsPanel::NativeConstruct()
{
    UMainGameInstance* GameInstance = Cast<UMainGameInstance>(GetGameInstance());
    
    if (GameInstance) {
        float Balance = GameInstance->StatsSubsystem->GetBalance();

        BalanceText->SetText(
            FText::FromString(
                FString::SanitizeFloat(round(Balance * 100) / 100) + "$")
        );
    }

    GameInstance->StatsSubsystem->BalanceDispatcher.AddDynamic(this, &UStatsPanel::OnBalanceChanged);
}

void UStatsPanel::OnBalanceChanged(float NewBalance)
{
    BalanceText->SetText(
        FText::FromString(
            FString::SanitizeFloat(round(NewBalance * 100) / 100) + "$")
    );
}
