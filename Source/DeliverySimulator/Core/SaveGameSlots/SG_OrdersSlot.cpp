// Fill out your copyright notice in the Description page of Project Settings.


#include "SG_OrdersSlot.h"

FOrder USG_OrdersSlot::AddOrder(TArray<FRestaurant>& AvailableRestaurants, TArray<FProduct>& AvailableProducts, TArray<FDestination>& AvailableDestinations)
{
	FOrder NewOrder = FOrder();
	if (CurrentOrders.Num() >= 10) return NewOrder;

	NewOrder.State = OrderState::NotTaken;

	if (CurrentOrders.Num() > 0) NewOrder.Id = CurrentOrders.Last().Id + 1;
	else NewOrder.Id = 1;
	
	NewOrder.Restaurant = AvailableRestaurants[FMath::RandRange(0, AvailableRestaurants.Num() - 1)];
	NewOrder.Destination = AvailableDestinations[FMath::RandRange(0, AvailableDestinations.Num() - 1)];
	NewOrder.PercentFee = FMath::RandRange(10, 45);

	int SumQuantity = FMath::RandRange(0, 8);
	
	for (auto Product : AvailableProducts)
	{
		if (SumQuantity <= 0) break;
		
		if (NewOrder.Restaurant.AvailableFoodIds.Contains(Product.Id))
		{
			FOrderProduct NewOrderProduct = FOrderProduct();
			NewOrderProduct.Product = Product;
			NewOrderProduct.Quantity = FMath::RandRange(1, SumQuantity);
			SumQuantity -= NewOrderProduct.Quantity;
			
			NewOrder.ProductList.Add(NewOrderProduct);
		}
	}
	if (NewOrder.ProductList.Num() == 0) {
		FOrderProduct NewOrderProduct = FOrderProduct();
			NewOrderProduct.Product = AvailableProducts[0];
			NewOrderProduct.Quantity = FMath::RandRange(1, SumQuantity);
			SumQuantity -= NewOrderProduct.Quantity;
			
			NewOrder.ProductList.Add(NewOrderProduct);
	}

	CurrentOrders.Add(NewOrder);
	return NewOrder;
}

void USG_OrdersSlot::RemoveOrder(FOrder& Order)
{
	for (int i = 0; i < CurrentOrders.Num(); i++) {
		if (CurrentOrders[i].Id == Order.Id) {
			CurrentOrders.RemoveAt(i);
			return;
		}
	}
}

FOrder USG_OrdersSlot::SetCurrentOrderDelivering(int Id) {
	for (auto Order : CurrentOrders) {
		if (Order.Id == Id) {
			CurrentOrderDelivering = Order;
			CurrentOrderDelivering.State = OrderState::OrderTaken;
			
			break;
		}
	}

	return CurrentOrderDelivering;
}

void USG_OrdersSlot::CancelCurrentOrderDelivering() {
	CurrentOrderDelivering = FOrder();
}

float FOrder::CalculateEarningsFloat()
{
    float OrderCost = 0;
	for (const FOrderProduct& Product : this->ProductList)
	{
		OrderCost += Product.Quantity * Product.Product.Price;
    }

	float ClearEarnings = (this->PercentFee * OrderCost) / 100.f;

	//return FString::SanitizeFloat(round(ClearEarnings * 100.f) / 100.f);
	return (round(ClearEarnings * 100.f) / 100.f);
}
FString FOrder::CalculateEarningsString()
{
	float ClearEarnings = CalculateEarningsFloat();

	return FString::SanitizeFloat(ClearEarnings);
}
