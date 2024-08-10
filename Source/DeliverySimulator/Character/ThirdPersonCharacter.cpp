// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DeliverySimulator/Core/MainGameInstance.h"

// Sets default values
AThirdPersonCharacter::AThirdPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();

	FRotator CameraRotation = Camera->GetComponentRotation();
	Camera->SetWorldRotation(FRotator(CameraRotation.Pitch, CameraRotation.Yaw, 0.f));
}

// Called every frame
void AThirdPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ClosestBicycle && WalkToBicycleState[0])
	{
		FVector GoalLocation = WalkToBicycleState[1] ?
			ClosestBicycle->GetMesh()->GetSocketLocation("get_from_right_socket") :
			ClosestBicycle->GetMesh()->GetSocketLocation("get_from_left_socket");
		FVector CharacterLocation = GetActorLocation();

		CharacterLocation.Z = 0;
		GoalLocation.Z = 0;

		if (CharacterLocation == GoalLocation ||
			(GetMovementComponent()->Velocity.Length() == 0.f && (CharacterLocation - GoalLocation).Length() < 100))
		{
			WalkToBicycleState[0] = false;
			OnMoveToBicycleComplete(WalkToBicycleState[1]);
		}
	}
}

// Called to bind functionality to input
void AThirdPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController *PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(CharacterMappingContext, 0);
		}
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AThirdPersonCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AThirdPersonCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AThirdPersonCharacter::StopJumping);
		EnhancedInputComponent->BindAction(GetInsideAction, ETriggerEvent::Started, this, &AThirdPersonCharacter::GetOnBicycleAction);
	}
}

void AThirdPersonCharacter::DestroyCharacterInput()
{
	if (APlayerController *PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->RemoveMappingContext(CharacterMappingContext);
		}
	}
}

void AThirdPersonCharacter::Move(const FInputActionValue &Value)
{
	const FVector2D CurrentValue = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();

	AddMovementInput(
		UKismetMathLibrary::GetForwardVector(FRotator(0.f, Rotation.Yaw, 0.f)),
		CurrentValue.Y
	);
	AddMovementInput(
		UKismetMathLibrary::GetRightVector(FRotator(0.f, Rotation.Yaw, Rotation.Roll)),
		CurrentValue.X
	);
}

void AThirdPersonCharacter::Look(const FInputActionValue &Value)
{
	const FVector2D CurrentValue = Value.Get<FVector2D>();

	if (GetController()) {
		AddControllerYawInput(CurrentValue.X);
		AddControllerPitchInput(CurrentValue.Y);
	}
}

void AThirdPersonCharacter::HandleEnterBicycleCollision(ABicycle* Bicycle)
{
	ClosestBicycle = Bicycle;
}

void AThirdPersonCharacter::HandleExitBicycleCollision(ABicycle* Bicycle)
{
	ClosestBicycle = nullptr;
}

void AThirdPersonCharacter::GetOnBicycleAction(const FInputActionValue &Value)
{
	if (ClosestBicycle && ClosestBicycle->GetMesh())
	{
		FVector BicycleToCharacter = GetActorLocation() - ClosestBicycle->GetActorLocation();
		BicycleToCharacter.Z = 0;

		FVector BicycleRightVector = ClosestBicycle->GetMesh()->GetRightVector();
		BicycleRightVector.Normalize();
		BicycleToCharacter.Normalize();
		
		const float DotProduct = FVector::DotProduct(BicycleToCharacter, BicycleRightVector);
		const FVector GoalLocation = DotProduct > 0 ?
			ClosestBicycle->GetMesh()->GetSocketLocation("get_from_right_socket") :
			ClosestBicycle->GetMesh()->GetSocketLocation("get_from_left_socket");
		
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), GoalLocation);
		WalkToBicycleState[0] = true;
		WalkToBicycleState[1] = DotProduct > 0;
	}
}

void AThirdPersonCharacter::OnMoveToBicycleComplete(const bool Side)
{
	const FRotator NewCharacterZRotation = Side ?
		ClosestBicycle->GetMesh()->GetSocketRotation("get_from_right_socket") :
		ClosestBicycle->GetMesh()->GetSocketRotation("get_from_left_socket");

	GetCharacterMovement()->DisableMovement();
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetWorldRotation(NewCharacterZRotation);

	FVector NewLocation= ClosestBicycle->GetMesh()->GetComponentLocation();
	NewLocation.Z -= 70.f;
	GetMesh()->SetWorldLocation(NewLocation);
	GetOnBicycleAnimation(Side);
}

void AThirdPersonCharacter::GetOnBicycleAnimation(bool Side)
{
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance(); AnimInstance && GetOnBicycleMontage)
	{
		if (!AnimInstance->Montage_IsPlaying(GetOnBicycleMontage) && ClosestBicycle)
		{
			
			int32 const SectionIndex = GetOnBicycleMontage->GetSectionIndex("Default");
			int32 const SectionLength = GetOnBicycleMontage->GetSectionLength(SectionIndex);

			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			PlayerController->SetViewTargetWithBlend(ClosestBicycle, 2.f);
			AnimInstance->Montage_Play(GetOnBicycleMontage);
			
			GetWorldTimerManager().SetTimer(GetInTransportTimer,this, &AThirdPersonCharacter::GetOnBicycle, SectionLength, false);
		}
		
	} else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "GetOnBicycleMontage not provided");
	}
}

void AThirdPersonCharacter::GetOnBicycle()
{
	// change state to right to not mirror animation
	WalkToBicycleState[1] = true;
	
	if (GetMesh())
		GetMesh()->SetVisibility(false);
		
	if (ClosestBicycle && ClosestBicycle->CharacterMesh)
		ClosestBicycle->CharacterMesh->SetVisibility(true);

	if (ClosestBicycle) {
		DestroyCharacterInput();
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(ClosestBicycle);
		this->Destroy();
	}
}

