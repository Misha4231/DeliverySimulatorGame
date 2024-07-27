// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "PhoneMenuIcon.generated.h"

class UMenuScreen;
/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UPhoneMenuIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UButton* IconButton;

	UPROPERTY(meta=(BindWidget))
	UImage* IconImage;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* AppTitleText;
	
	UFUNCTION()
	void OnButtonClicked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* InitialIconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText InitialIconTitle;
	
	UFUNCTION(BlueprintCallable)
	void SetIconTexture(UTexture2D* IconTexture) const;

	UFUNCTION(BlueprintCallable)
	void SetTitle(const FText& NewTitle) const;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//int WidgetSwitcherIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> IconScreen;

	UPROPERTY()
	UMenuScreen* MenuScreenObject;
	void (UMenuScreen::*OnChangeScreen)(TSubclassOf<UUserWidget>);
};
