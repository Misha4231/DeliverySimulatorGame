// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"
#include "Components/SizeBox.h"
#include "Phone/PhoneCore.h"
#include "Stats/StatsPanel.h"
#include "Components/GridPanel.h"
#include "Kismet/GameplayStatics.h"
#include "CoreHUD.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UCoreHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	USizeBox* OverlayPhonePosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Phone")
	UPhoneCore* PhoneWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Phone")
	TSubclassOf<UPhoneCore> PhoneWidgetBlueprintClass;

	UFUNCTION(BlueprintCallable, Category="Phone")
	void GetInPhone();

	UFUNCTION(BlueprintCallable, Category="Phone")
	void HidePhone();

public:
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	USizeBox* StatsWrapper;

	UPROPERTY(EditAnywhere, Category="Stats", meta=(BindWidget))
	UStatsPanel *StatsWidget;
};
