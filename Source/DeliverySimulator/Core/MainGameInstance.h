// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Subsystems/StatsSubsystem.h"
#include "Subsystems/OrdersSubsystem.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Orders")
	UOrdersSubsystem *OrdersSubsystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orders")
	UDataTable* ProductsDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats")
	UStatsSubsystem* StatsSubsystem;
};
