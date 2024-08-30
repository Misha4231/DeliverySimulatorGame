// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonWidget.h"

void UButtonWidget::NativePreConstruct()
{
    if (Text) {
        Text->SetText(ButtonText);
        Text->SetFont(TextFont);
    }

    if (Button) {
        Button->OnClicked.AddUniqueDynamic(this, &UButtonWidget::OnClickedEvent);
        Button->OnHovered.AddUniqueDynamic(this, &UButtonWidget::OnHoveredEvent);
        Button->OnUnhovered.AddUniqueDynamic(this, &UButtonWidget::OnUnhoveredEvent);
        Button->OnPressed.AddUniqueDynamic(this, &UButtonWidget::OnPressedEvent);
    }
}

void UButtonWidget::OnClickedEvent()
{
    if (OnClickSound)
        UGameplayStatics::PlaySound2D(GetWorld(), OnClickSound);

    FTimerHandle DelayHandle;
    
    GetWorld()->GetTimerManager().SetTimer(DelayHandle, this, &UButtonWidget::CallClickDelegate, 0.4f, false);
}

void UButtonWidget::CallClickDelegate() {
    if (OnClickedDelegate.IsBound()) {
        OnClickedDelegate.Execute();
    }
}
void UButtonWidget::OnHoveredEvent()
{
    if (OnHoverSound) {
        UGameplayStatics::PlaySound2D(GetWorld(), OnHoverSound);
    }
        
    PlayAnimation(HoverAnimation);
}

void UButtonWidget::OnUnhoveredEvent()
{
    if (OnUnhoverSound) {
        UGameplayStatics::PlaySound2D(GetWorld(), OnUnhoverSound);
    }

    PlayAnimationReverse(HoverAnimation);
}

void UButtonWidget::OnPressedEvent()
{
    PlayAnimationReverse(HoverAnimation, 1.5f);
}
