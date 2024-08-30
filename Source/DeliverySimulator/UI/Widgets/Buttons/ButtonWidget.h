// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Delegates/Delegate.h"
#include "Kismet/GameplayStatics.h"
#include "ButtonWidget.generated.h"

DECLARE_DELEGATE(EDispatchOnClicked);

/**
 * 
 */
UCLASS()
class DELIVERYSIMULATOR_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void virtual NativePreConstruct() override;

	UPROPERTY(meta=(BindWidget))
	UButton *Button;

	UPROPERTY(meta=(BindWidget))
	UTextBlock *Text;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText ButtonText;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSlateFontInfo TextFont;

protected:
	UFUNCTION()
	void OnClickedEvent();
	void CallClickDelegate();

	UFUNCTION()
	void OnHoveredEvent();

	UFUNCTION()
	void OnUnhoveredEvent();

	UFUNCTION()
	void OnPressedEvent();

	UPROPERTY(Transient ,meta=(BindWidgetAnim))
	UWidgetAnimation* HoverAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase *OnClickSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase *OnHoverSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase *OnUnhoverSound;

public:
	EDispatchOnClicked OnClickedDelegate;
};
