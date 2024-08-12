// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"
#include "ChaosVehicleMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AVehicle::AVehicle() {
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(CameraBoom);
}

void AVehicle::BeginPlay() {
    Super::BeginPlay();
}

void AVehicle::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (APlayerController* PlayerContoller = Cast<APlayerController>(GetController())) {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerContoller->GetLocalPlayer())) {
            Subsystem->AddMappingContext(VehicleMappingContext, 0);
        }
    }

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVehicle::Ride);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AVehicle::Look);
        EnhancedInputComponent->BindAction(HandBrakeAction, ETriggerEvent::Started, this, &AVehicle::HandBrake);
        EnhancedInputComponent->BindAction(HandBrakeAction, ETriggerEvent::Completed, this, &AVehicle::HandBrake);
        EnhancedInputComponent->BindAction(GetOutAction, ETriggerEvent::Started, this, &AVehicle::GetOut);

        RideActionBinding = &EnhancedInputComponent->BindActionValue(MoveAction);
    }
}
void AVehicle::DestroyVehicleInput()
{
    if (APlayerController* PlayerContoller = Cast<APlayerController>(GetController())) {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerContoller->GetLocalPlayer())) {
            Subsystem->RemoveMappingContext(VehicleMappingContext);
        }
    }
}

void AVehicle::Ride(const FInputActionValue &Value)
{
    const FVector2D CurrentValue = Value.Get<FVector2D>();

    GetVehicleMovementComponent()->SetThrottleInput(CurrentValue.Y);    
    GetVehicleMovementComponent()->SetBrakeInput(-CurrentValue.Y);
    GetVehicleMovementComponent()->SetSteeringInput(CurrentValue.X);
}

void AVehicle::Look(const FInputActionValue& Value)
{
    const FVector2D CurrentValue = Value.Get<FVector2D>();

    if (GetController()) {
		AddControllerYawInput(CurrentValue.X);
		AddControllerPitchInput(CurrentValue.Y);
	}
}

void AVehicle::HandBrake(const FInputActionValue& Value)
{
    const bool CurrentValue = Value.Get<bool>();
    GetVehicleMovementComponent()->SetHandbrakeInput(CurrentValue);
}

float AVehicle::GetYRideAxis() const
{
    if (RideActionBinding) {
        const FVector2D RideValue = RideActionBinding->GetValue().Get<FVector2D>();
        return RideValue.Y;
    }
    return 0.f;
}
