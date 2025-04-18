// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "./Screens/Base/PhoneScreen.h"
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
	UBorder* ScreensWrapper;

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
	UWidgetAnimation *FadeOut;

	UPROPERTY()
	UCoreHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPhoneScreen> MenuScreenClass;

	UPROPERTY(BlueprintReadOnly)
	TArray<UPhoneScreen*> ScreensStack;
	
	UFUNCTION(BlueprintCallable)
	void ChangeScreen(TSubclassOf<UPhoneScreen> NewScreenClass);

	UFUNCTION(BlueprintCallable)
	void ChangeToCreatedScreen(UPhoneScreen* NewScreen);

	void UpdateBackground();
	void ShowCurrentTopScreen();
	
	UFUNCTION()
	void GoHomeScreen();

	UFUNCTION()
	void GoBackScreen();

private:
	FScreenChangeDelegate ScreenChangeDelegate;
	FChangeToCreatedScreenDelegate ChangeToCreatedScreenDelegate;
};
