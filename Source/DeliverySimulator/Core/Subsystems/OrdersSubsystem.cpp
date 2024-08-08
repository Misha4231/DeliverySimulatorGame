// Fill out your copyright notice in the Description page of Project Settings.


#include "OrdersSubsystem.h"
#include "Kismet/GameplayStatics.h"


void UOrdersSubsystem::InitializeSubsystem(UDataTable *ProductsDataTable, FTimerManager& TimerManger)
{

    if (ProductsDataTable)
	{
		
		const FString ContextString(TEXT("Product Data Context"));
		TArray<FProduct*> TempArray;
		ProductsDataTable->GetAllRows<FProduct>(ContextString, TempArray);

		for (const FProduct* Product : TempArray)
		{
			Products.Add(*Product);
		}
	}

	LoadOrdersSlotData();
	TimerManger.SetTimer(OrdersTimerHandle,this, &UOrdersSubsystem::AddOrder, 5.f, true);
}


const TArray<FProduct>& UOrdersSubsystem::GetProducts() const
{
	return Products;
}

TArray<FOrder>& UOrdersSubsystem::GetCurrentOrders()
{
	LoadOrdersSlotData();
	return OrdersSave->CurrentOrders;
}


FOrder& UOrdersSubsystem::GetCurrentOrder()
{
    LoadOrdersSlotData();

	return OrdersSave->CurrentOrderDelivering;
}

FOrder UOrdersSubsystem::SetCurrentOrder(int Id)
{
	LoadOrdersSlotData();

	FOrder Order = OrdersSave->SetCurrentOrderDelivering(Id);
	SaveOrdersSlotData();

	return Order;
}

void UOrdersSubsystem::SetCurrentOrderState(OrderState NewState)
{
	LoadOrdersSlotData();
	
	if (NewState == OrderState::NotTaken) {
		OrdersSave->RemoveOrder(OrdersSave->CurrentOrderDelivering);
		OrdersSave->CurrentOrderDelivering = FOrder();
		
	} else {
		OrdersSave->CurrentOrderDelivering.State = NewState;
	}

	SaveOrdersSlotData();
}

void UOrdersSubsystem::LoadOrdersSlotData()
{
	if(UGameplayStatics::DoesSaveGameExist(OrdersSaveSlotName, 0))
	{
		OrdersSave = Cast<USG_OrdersSlot>(UGameplayStatics::LoadGameFromSlot(OrdersSaveSlotName, 0));
	} else
	{
		OrdersSave = Cast<USG_OrdersSlot>(UGameplayStatics::CreateSaveGameObject(USG_OrdersSlot::StaticClass()));
		UGameplayStatics::SaveGameToSlot(OrdersSave, OrdersSaveSlotName, 0);
	}
}

void UOrdersSubsystem::SaveOrdersSlotData()
{
	if(UGameplayStatics::DoesSaveGameExist(OrdersSaveSlotName, 0))
	{
		UGameplayStatics::SaveGameToSlot(OrdersSave, OrdersSaveSlotName, 0);
		
	} else
	{
		OrdersSave = Cast<USG_OrdersSlot>(UGameplayStatics::CreateSaveGameObject(USG_OrdersSlot::StaticClass()));
		UGameplayStatics::SaveGameToSlot(OrdersSave, OrdersSaveSlotName, 0);
	}
}

void UOrdersSubsystem::AddOrder()
{
	FOrder NewOrder = OrdersSave->AddOrder(Restaurants, Products, Destinations);

	if (NewOrder.Id != 0) {
		SaveOrdersSlotData();
		LoadOrdersSlotData();

		NewOrderDispatcher.Broadcast(NewOrder);
	}
}