// Fill out your copyright notice in the Description page of Project Settings.


#include "PhoneMenuIcon.h"

void UPhoneMenuIcon::NativeConstruct()
{
	Super::NativeConstruct();

	SetIconTexture(InitialIconTexture);
	SetTitle(InitialIconTitle);
	
	IconButton->OnClicked.AddUniqueDynamic(this, &UPhoneMenuIcon::OnButtonClicked);
}

void UPhoneMenuIcon::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetIconTexture(InitialIconTexture);
	SetTitle(InitialIconTitle);
}

void UPhoneMenuIcon::OnButtonClicked()
{
	if (ScreenChangeDelegate && ScreenChangeDelegate->IsBound()) {
		ScreenChangeDelegate->Execute(IconScreen);
	}
}

void UPhoneMenuIcon::SetIconTexture(UTexture2D* IconTexture) const
{
	if (IconTexture)
	{
		IconImage->SetVisibility(ESlateVisibility::Visible);
		IconImage->SetBrushFromTexture(IconTexture);
	}
	else
	{
		IconImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPhoneMenuIcon::SetTitle(const FText& NewTitle) const
{
	AppTitleText->SetText(NewTitle);
}
