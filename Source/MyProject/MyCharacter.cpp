// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachement(RootComponent);
	Camera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	FVector Start = Camera->GetComponentLocation();

	FVector Forward = Camera->GetForwardVector();

	FVector End = ((Forward * 1000.0f) + Start);

	FHitResult outHit;

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

	TArray<AActor*> ignore;
	ignore.Add(GetOwner());

	bool result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, TraceObjectTypes, false, ignore, EDrawDebugTrace::ForOneFrame, OUT outHit, true);

	if (result) {
		FString f = FString(outHit.GetActor()->GetName());

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, f);
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)){

		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveForward);

	}

	if(APlayerController* PlayerController = Cast<APlayerController>(Controller)){ //adding input mapping context

		// setting local player subsystem
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()));
		{
			// adding input context
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)){

		Input->BindAction(TestAction, ETriggerEvent::Triggered, this, &AMyCharacter::NewInput); //It's binding Input to NewInput aka what it needs to do?
	}

}

void AMyCharacter::NewInput() //this is the input that it calls to do
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Pressed Input!!");

}

void AMyCharacter::MoveForward(const FInputActionValue& InputValue){

	FVector2D InputVector = InputValue.Get<FVector2D>();

	if(IsValid(Controller))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}
} 

void AMyCharacter::TestingInterface_Implementation()
{
	if(GEngine){

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString(TEXT("Interface Called!!! :D")));
	}
}
