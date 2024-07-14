// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCharacter.h"

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

	// Camera
	PlayerInputComponent->BindAxis("LookRight", this, &AThirdPersonCharacter::LookRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AThirdPersonCharacter::LookUp);

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AThirdPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("TurnLeft", this, &AThirdPersonCharacter::TurnLeft);
	PlayerInputComponent->BindAxis("MoveBack", this, &AThirdPersonCharacter::MoveBack);

	// Jumping
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AThirdPersonCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AThirdPersonCharacter::StopJumping);

	// Animations
	PlayerInputComponent->BindAction("GetInside", IE_Pressed, this, &AThirdPersonCharacter::GetOnBicycleAction);
}

void AThirdPersonCharacter::HandleEnterBicycleCollision(ABicycle* Bicycle)
{
	ClosestBicycle = Bicycle;
}

void AThirdPersonCharacter::HandleExitBicycleCollision(ABicycle* Bicycle)
{
	ClosestBicycle = nullptr;
}

void AThirdPersonCharacter::LookRight(const float Scale)
{
	AddControllerYawInput(Scale);
}

void AThirdPersonCharacter::LookUp(const float Scale)
{
	AddControllerPitchInput(Scale);
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::SanitizeFloat(Scale));
}

void AThirdPersonCharacter::MoveForward(const float Scale)
{
	const FRotator Rotation = GetControlRotation();
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0, Rotation.Yaw, 0)), Scale);
}
void AThirdPersonCharacter::MoveBack(const float Scale)
{
	MoveForward(Scale);
}

void AThirdPersonCharacter::TurnLeft(const float Scale)
{
	const FRotator Rotation = GetControlRotation();
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0, Rotation.Yaw, Rotation.Roll)), Scale);
}

void AThirdPersonCharacter::GetOnBicycleAction()
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
	
	GetMesh()->SetVisibility(false);
	ClosestBicycle->CharacterMesh->SetVisibility(true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(ClosestBicycle);
}



