// Fill out your copyright notice in the Description page of Project Settings.


#include "ProductsListEntry.h"
#include "ProductPassObject.h"

void UProductsListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UProductPassObject *ProductObject = Cast<UProductPassObject>(ListItemObject);
	if (ProductObject) {
		Title->SetText(FText::FromString(ProductObject->Product.Product.Name));
		Quantity->SetText(FText::FromString(
			FString::FormatAsNumber(ProductObject->Product.Quantity) + " x " + FString::SanitizeFloat(round(ProductObject->Product.Product.Price * 100) * 0.01) + FString("$")
		));

		SumPrice->SetText(FText::FromString(
			FString("Total: ") + FString::SanitizeFloat(round((ProductObject->Product.Product.Price * ProductObject->Product.Quantity) * 100) * 0.01) + FString("$")
		));
	}
}
