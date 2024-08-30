// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdersListEntry.h"
#include "ProductPassObject.h"
#include "Kismet/GameplayStatics.h"
#include "../Screens/Orders/OrderDetailsScreen.h"

void UOrdersListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	OrderData = Cast<UOrderPassObject>(ListItemObject);

	if (OrderData)
	{
		Logo->SetBrushFromTexture(OrderData->Order.Restaurant.Logo);

		Earnings->SetText(FText::FromString(
			OrderData->Order.CalculateEarningsString() + "$"
		));

		RestaurantName->SetText(FText::FromString(
			OrderData->Order.Restaurant.Name));
		DestinationName->SetText(FText::FromString(
			OrderData->Order.Destination.Name));

		ProductsVisualizationWrapper->ClearChildren();
		for (int ProductIdx = 0; ProductIdx < OrderData->Order.ProductList.Num(); ProductIdx++) {
			UImage *ProductImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
			
			ProductImage->SetBrushFromTexture(OrderData->Order.ProductList[ProductIdx].Product.Image);
			ProductImage->SetRenderTranslation(FVector2D(ProductIdx * 10 * (-1), 0));
			
			ProductsVisualizationWrapper->AddChildToHorizontalBox(ProductImage);
		}

		OrderData->ListItemSelectedDelegate->AddUObject(this, &UOrdersListEntry::OnListItemSelected);
	}
	
}

void UOrdersListEntry::NativeConstruct()
{
	Super::NativeConstruct();

	TopEmissivePipe->SetVisibility(ESlateVisibility::Hidden);
	BottomEmissivePipe->SetVisibility(ESlateVisibility::Hidden);

	ClickableWrapper->OnClicked.AddDynamic(this, &UOrdersListEntry::OnEntryClicked);
	ClickableWrapper->OnHovered.AddDynamic(this, &UOrdersListEntry::OnEntryHovered);
	ClickableWrapper->OnUnhovered.AddDynamic(this, &UOrdersListEntry::OnEntryUnhovered);

	OnHoverAnimationEndDelegate.BindUFunction(this, "OnHoverAnimationEnd");
	BindToAnimationFinished(HoverLinesAnimation, OnHoverAnimationEndDelegate);
}

void UOrdersListEntry::OnEntryClicked()
{
	if (SelectionSound)
		UGameplayStatics::PlaySound2D(GetWorld(), SelectionSound);


	if (isSelected) {
		if (UOrderDetailsScreen *OrderDetailsScreenWidget = Cast<UOrderDetailsScreen>(CreateWidget<UUserWidget>(this, OrderDetailsScreenClass))) {
			OrderDetailsScreenWidget->SetOrderData(OrderData);

			if (OrderData->ChangeToCreatedScreenDelegate->IsBound()) {
				OrderData->ChangeToCreatedScreenDelegate->Execute(OrderDetailsScreenWidget);
			}
		}
		return;
	}

	isSelected = true;
	
	if (OrderData->ListItemSelectedDelegate->IsBound()) {
		OrderData->ListItemSelectedDelegate->Broadcast(OrderData);
	}
}

void UOrdersListEntry::OnListItemSelected(UOrderPassObject *SelectedOrderData)
{
	if (SelectedOrderData->Order.Id != OrderData->Order.Id && isSelected) {
		isSelected = false;
		PlayAnimationReverse(HoverLinesAnimation);
	}
}

void UOrdersListEntry::OnEntryHovered() {
	if (!isSelected) {
		if (HoverSound)
			UGameplayStatics::PlaySound2D(GetWorld(), HoverSound);

		TopEmissivePipe->SetVisibility(ESlateVisibility::Visible);
		BottomEmissivePipe->SetVisibility(ESlateVisibility::Visible);

		if (HoverLinesAnimation) {
			PlayAnimation(HoverLinesAnimation);
			
		}
	}
}
void UOrdersListEntry::OnEntryUnhovered() {
	if (HoverLinesAnimation && !isSelected) {
		PlayAnimationReverse(HoverLinesAnimation);
	}

}

void UOrdersListEntry::OnHoverAnimationEnd()
{
	if (ClickableWrapper->IsHovered()) {
		TopEmissivePipe->SetVisibility(ESlateVisibility::Visible);
		BottomEmissivePipe->SetVisibility(ESlateVisibility::Visible);
	} else {
		TopEmissivePipe->SetVisibility(ESlateVisibility::Hidden);
		BottomEmissivePipe->SetVisibility(ESlateVisibility::Hidden);	
	}
}
