// Fill out your copyright notice in the Description page of Project Settings.


#include "OrderDetailsScreen.h"
#include <DeliverySimulator/Core/MainGameInstance.h>

void UOrderDetailsScreen::ScreenConstruct()
{
    Restaurant->SetText(FText::FromString(OrderData->Order.Restaurant.Name));
    Destination->SetText(FText::FromString(OrderData->Order.Destination.Name));
    Logo->SetBrushFromTexture(OrderData->Order.Restaurant.Logo);

    PercentFee->SetText(FText::FromString(
		FString::FormatAsNumber(OrderData->Order.PercentFee) + "%"
	));

	for (const FOrderProduct& Product : OrderData->Order.ProductList)
	{
        UProductPassObject *ProductData = NewObject<UProductPassObject>(this);
        ProductData->Product = Product;
        
        ProductsListView->AddItem(ProductData);
    }
    
    Earnings->SetText(FText::FromString(
		OrderData->Order.CalculateEarningsString() + "$"
	));

    TakeOrderButton->OnClickedDelegate.BindUObject(this, &UOrderDetailsScreen::TakeOrderButtonClicked);
}


void UOrderDetailsScreen::SetOrderData(UOrderPassObject* InOrderData)
{
    OrderData = InOrderData;
}

void UOrderDetailsScreen::TakeOrderButtonClicked() {
    if (UMainGameInstance *GameInstance = Cast<UMainGameInstance>(GetGameInstance())) {
        GameInstance->OrdersSubsystem->SetCurrentOrder(OrderData->Order.Id);

        TakeOrderButton->SetIsEnabled(false);
    }
}