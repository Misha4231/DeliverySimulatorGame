// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdersScreen.h"
#include "DeliverySimulator/UI/Phone/Components/OrderPassObject.h"
#include "OrderDetailsScreen.h"

void UOrdersScreen::ScreenConstruct()
{
	MainGameInstance = Cast<UMainGameInstance>(GetGameInstance());
	UE_LOG(LogTemp, Warning, TEXT("Orders list construct"));
	
	FOrder &CurrentDelieringOrder = MainGameInstance->OrdersSubsystem->GetCurrentOrder();
	if (MainGameInstance && MainGameInstance->OrdersSubsystem) {
		if (CurrentDelieringOrder.Id == 0) {
			CurrentOrderWrapper->SetVisibility(ESlateVisibility::Hidden);
			OrdersListWrapper->SetVisibility(ESlateVisibility::Visible);
		} else {
			OrdersListWrapper->SetVisibility(ESlateVisibility::Hidden);
			CurrentOrderWrapper->SetVisibility(ESlateVisibility::Visible);

			RestaurantTitle->SetText(FText::FromString(CurrentDelieringOrder.Restaurant.Name));
			DestinationTitle->SetText(FText::FromString(CurrentDelieringOrder.Destination.Name));
			
			TotalEarnings->SetText(FText::FromString(
				CurrentDelieringOrder.CalculateEarningsString()
			));
		}

		TArray<FOrder>& CurrentOrders = MainGameInstance->OrdersSubsystem->GetCurrentOrders();
		for (int i = 0; i<CurrentOrders.Num(); i++) {
			OnAddOrderToList(CurrentOrders[i]);
		}
		MainGameInstance->OrdersSubsystem->NewOrderDispatcher.AddUniqueDynamic(this, &UOrdersScreen::OnAddOrderToList);
	}
}

void UOrdersScreen::OnAddOrderToList(FOrder NewOrder)
{
	UOrderPassObject* PassObject = NewObject<UOrderPassObject>(this);
	PassObject->Order = NewOrder;
	PassObject->ScreenChangeDelegate = ScreenChangeDelegate;
	PassObject->ChangeToCreatedScreenDelegate = ChangeToCreatedScreenDelegate;

	OrdersList->AddItem(PassObject);
}
