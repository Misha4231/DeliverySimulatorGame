// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreensRouting.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "DeliverySimulator/UI/Phone/PhoneMenuIcon.h"
#include "MenuScreen.generated.h"

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UMenuScreen : public UUserWidget, public IScreenRoutingInterface
{
	GENERATED_BODY()

public:
	virtual void SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate, FChangeToCreatedScreenDelegate InChangeToCreatedScreenDelegate);
protected:
	FScreenChangeDelegate ScreenChangeDelegate;

public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UGridPanel* MenuIcons;

	UPROPERTY(BlueprintReadOnly)
	TArray<UPhoneMenuIcon*> MenuButtons;

	UFUNCTION(BlueprintCallable)
	void CacheButtons();

	void ChangeScreen(TSubclassOf<UUserWidget> NewScreen);
};
