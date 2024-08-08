// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "StatsPanel.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UStatsPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UTextBlock *BalanceText;

private:
	UFUNCTION()
	void OnBalanceChanged(float NewBalance);
};

