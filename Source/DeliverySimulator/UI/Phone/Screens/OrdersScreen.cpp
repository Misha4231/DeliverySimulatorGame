// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdersScreen.h"
#include "DeliverySimulator/UI/Phone/Components/RestaurantPassObject.h"
#include "OrderDetailsScreen.h"

void UOrdersScreen::SetScreenChangeDelegate(FScreenChangeDelegate InScreenChangeDelegate, FChangeToCreatedScreenDelegate InChangeToCreatedScreenDelegate)
{
	ScreenChangeDelegate = InScreenChangeDelegate;
	ChangeToCreatedScreenDelegate = InChangeToCreatedScreenDelegate;
}

void UOrdersScreen::NativeConstruct()
{
	Super::NativeConstruct();

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
		MainGameInstance->OrdersSubsystem->NewOrderDispatcher.AddDynamic(this, &UOrdersScreen::OnAddOrderToList);
	}
}

void UOrdersScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UOrdersScreen::OnOrderTaken(int Id) {
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString("Order #") + FString::FormatAsNumber(Id) + FString(" taken"));

	if (MainGameInstance && MainGameInstance->OrdersSubsystem) {
		MainGameInstance->OrdersSubsystem->SetCurrentOrder(Id);

		if (ScreenChangeDelegate.IsBound()) {
			ScreenChangeDelegate.Execute(OrdersScreenClass);
		}
	}
}

void UOrdersScreen::OnGoToDetails(URestaurantPassObject* SelectedOrder) {
	if (UOrderDetailsScreen* OrderDetailsScreenWidget = Cast<UOrderDetailsScreen>(CreateWidget<UUserWidget>(this, OrderDetailsScreenClass))) {

		OrderDetailsScreenWidget->SetOrderData(SelectedOrder);

		if (ChangeToCreatedScreenDelegate.IsBound()) {
			ChangeToCreatedScreenDelegate.Execute(OrderDetailsScreenWidget);
		}
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString("Go to details of order #") + FString::FormatAsNumber(SelectedOrder->Order.Id));
}

void UOrdersScreen::OnAddOrderToList(FOrder NewOrder)
{
	URestaurantPassObject* PassObject = NewObject<URestaurantPassObject>(this);
	PassObject->Order = NewOrder;
	PassObject->OrdersScreenObject = this;
	PassObject->OnOrderTaken = &UOrdersScreen::OnOrderTaken;
	PassObject->OnGoToDetails = &UOrdersScreen::OnGoToDetails;

	OrdersList->AddItem(PassObject);
}
