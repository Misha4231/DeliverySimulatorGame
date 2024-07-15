// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
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

	UPROPERTY(meta=(BindWidget))
	UImage* HeaderBackground;

	UPROPERTY(meta=(BindWidget))
	UBorder* ScreenSwitcherWrapper;

	UPROPERTY(meta=(BindWidget))
	UBorder* GoBackSectionWrapper;

	UPROPERTY(meta=(BindWidget))
	UButton* BackButton;
	
	UFUNCTION(BlueprintCallable)
	void OnHidePhoneAnimation();

	UFUNCTION(BlueprintCallable)
	void OnHidePhone();
	
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* FadeIn;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* FadeOut;

	UPROPERTY()
	UCoreHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UUserWidget>> ScreenClassesArray;

	UPROPERTY(BlueprintReadOnly)
	TArray<UUserWidget*> ScreensArray;
	
	UFUNCTION(BlueprintCallable)
	void ChangeScreen(const int ActiveWidgetIndex);

	void UpdateBackground();
	
	UFUNCTION()
	void GoHomeScreen();
};
