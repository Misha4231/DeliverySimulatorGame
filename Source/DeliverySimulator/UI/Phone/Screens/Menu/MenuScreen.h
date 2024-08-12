// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Base/PhoneScreen.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "DeliverySimulator/UI/Phone/PhoneMenuIcon.h"
#include "MenuScreen.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UMenuScreen : public UPhoneScreen
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	UGridPanel* MenuIcons;

	UPROPERTY(BlueprintReadOnly)
	TArray<UPhoneMenuIcon*> MenuButtons;

	UFUNCTION(BlueprintCallable)
	void CacheButtons();

public:
	virtual void ScreenConstruct() override;
};
