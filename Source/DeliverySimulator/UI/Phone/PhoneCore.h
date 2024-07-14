// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "PhoneCore.generated.h"

class UCoreHUD;
/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UPhoneCore : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CurrentTimeTextBlock;

	UPROPERTY(meta=(BindWidget))
	UWidgetSwitcher* ScreensSwitcher;

	UFUNCTION(BlueprintCallable)
	void OnHidePhoneAnimation();

	UFUNCTION(BlueprintCallable)
	void OnHidePhone();

	UFUNCTION(BlueprintCallable)
	void SetPhoneWidget(UWidget* Screen);
	
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* FadeIn;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* FadeOut;

	UPROPERTY()
	UCoreHUD* HUD;

	UFUNCTION(BlueprintCallable)
	void ChangeScreen(const int ActiveWidgetIndex);
};
