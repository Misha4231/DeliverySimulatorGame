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

const TArray<FOrder>& UOrdersSubsystem::GetCurrentOrders() const
{
	return Orders;
}

const int UOrdersSubsystem::GetCurrentOrdersLength() const
{
	return Orders.Num();
}

void UOrdersSubsystem::CurrentOrderDone()
{
	LoadOrdersSlotData();
	OrdersSave->CancelCurrentOrderDelivering();

	// Give Money on balance
}

void UOrdersSubsystem::CancelCurrentOrder()
{
	LoadOrdersSlotData();
	OrdersSave->CancelCurrentOrderDelivering();
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

void UOrdersSubsystem::LoadOrdersSlotData()
{
	if(UGameplayStatics::DoesSaveGameExist(OrdersSaveSlotName, 0))
	{
		OrdersSave = Cast<USG_OrdersSlot>(UGameplayStatics::LoadGameFromSlot(OrdersSaveSlotName, 0));
		if (OrdersSave)
		{
			Orders = OrdersSave->CurrentOrders;
		}
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
	OrdersSave->AddOrder(Restaurants, Products, Destinations);
	SaveOrdersSlotData();
	LoadOrdersSlotData();
}