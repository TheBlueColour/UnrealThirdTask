// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Super::SetupPlayerInputComponent(PlayerInputComponent);
    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    // Input->BindAction(AimingInputAction, ETriggerEvent::Triggered, this, &AMyPawn::SomeCallbackFunc);

    /*if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (MoveForwardAction)
        {
            EnhancedInput->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AMyPawn::MoveForward);
        }
        if (MoveRightAction)
        {
            EnhancedInput->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AMyPawn::MoveRight);
        }
    }*/

}

//void AMyPawn::MoveForward(FInputActionValue& Value)
//{
//
//}
//
//void AMyPawn::MoveRight(FInputActionValue& Value)
//{
//
//}

