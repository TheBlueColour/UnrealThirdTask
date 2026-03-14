// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyCharacter.generated.h"
#include "Kismet/KismetSystemLibrary.h"

UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter , public IMyInterface3 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(EditAnywhere, Category =  "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	class UInputAction* TestAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	class UInputAction* MoveAction;

	void NewInput();

	void MoveForward(const FInputActionValue& InputValue);

public:

	virtual void TestingInterface_Implementation() override;

protected:

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

};
