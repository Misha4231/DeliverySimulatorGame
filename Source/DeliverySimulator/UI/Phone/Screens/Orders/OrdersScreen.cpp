// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdersScreen.h"
#include "DeliverySimulator/UI/Phone/Components/OrderPassObject.h"
#include "../../Components/OrderPassObject.h"
#include "OrderDetailsScreen.h"

void UOrdersScreen::ScreenConstruct()
{
	MainGameInstance = Cast<UMainGameInstance>(GetGameInstance());
	
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

	DetailsButtonWrapper->SetVisibility(ESlateVisibility::Collapsed);

	DetailsButton->OnClickedDelegate.BindUObject(this, &UOrdersScreen::OnDetailsButtonClicked);
	OnListItemSlectedDelegate.AddUObject(this, &UOrdersScreen::OnListItemSelected);
}

void UOrdersScreen::OnDetailsButtonClicked()
{
	if (!SelectedOrderData) return;

	if (UOrderDetailsScreen* DetailsScreen = Cast<UOrderDetailsScreen>(CreateWidget<UPhoneScreen>(this, OrderDetailsScreenClass))) {
		DetailsScreen->SetOrderData(SelectedOrderData);
		
		if (ChangeToCreatedScreenDelegate->IsBound()) {
			ChangeToCreatedScreenDelegate->Execute(DetailsScreen);
		}
	}


	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Clicked"));
}

void UOrdersScreen::OnListItemSelected(UOrderPassObject* OrderData)
{
	SelectedOrderData = OrderData;
	DetailsButtonWrapper->SetRenderOpacity(0.1);
	DetailsButtonWrapper->SetVisibility(ESlateVisibility::Visible);

	if (DetailsButtonShowupAnimation)
		PlayAnimation(DetailsButtonShowupAnimation);
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, "Selected");
}

void UOrdersScreen::OnAddOrderToList(FOrder NewOrder)
{
	UOrderPassObject* PassObject = NewObject<UOrderPassObject>(this);
	PassObject->Order = NewOrder;
	PassObject->ScreenChangeDelegate = ScreenChangeDelegate;
	PassObject->ChangeToCreatedScreenDelegate = ChangeToCreatedScreenDelegate;
	PassObject->ListItemSelectedDelegate = &OnListItemSlectedDelegate;

	OrdersList->AddItem(PassObject);
}
