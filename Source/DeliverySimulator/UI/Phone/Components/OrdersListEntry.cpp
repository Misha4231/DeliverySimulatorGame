// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdersListEntry.h"
#include "ProductPassObject.h"
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
	}
}

void UOrdersListEntry::NativeConstruct()
{
	Super::NativeConstruct();

	GoToDetailsButton->OnClicked.AddDynamic(this, &UOrdersListEntry::GoToDetails);
}

void UOrdersListEntry::GoToDetails()
{
	if (UOrderDetailsScreen *OrderDetailsScreenWidget = Cast<UOrderDetailsScreen>(CreateWidget<UUserWidget>(this, OrderDetailsScreenClass))) {
		OrderDetailsScreenWidget->SetOrderData(OrderData);

		if (OrderData->ChangeToCreatedScreenDelegate->IsBound()) {
			OrderData->ChangeToCreatedScreenDelegate->Execute(OrderDetailsScreenWidget);
		}
	}
}
