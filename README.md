# UnrealThirdTask - Working with Enhanced Input in C++

I worked on allowing the player to move left and right within the level, for this in the editor I had to create a C++ class of a pawn as well as a Blueprint class of the InputCharacter pawn so that it is able to recognise changes we made in the C++ class. Additionally in the editor I had to create an Gamemode that will run the Player blueprint with the movement abiltiy, as well as Input mapping context for Unreal to be able to take in input from the player, binding the mapping to 'A' and 'D' to move left and right. As well as a seperate "NewInput" that displays a message upon an 'E' press. 

In the C++ pawn of the .cpp header I had to first call to bind the functionality to input in the "SetUpPlayerInput".

```
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) //the function of SetUpPlayerInput, calling a pointer of PlayerInputComponent. 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)){

		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveForward); //The input is binded to another function in the c++ player

	}

	if(APlayerController* PlayerController = Cast<APlayerController>(Controller)){ //adding input mapping context

		// setting local player subsystem
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// adding input context
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)){

		Input->BindAction(TestAction, ETriggerEvent::Triggered, this, &AMyCharacter::NewInput); //It's binding the Input to NewInput another function in the c++ player
	}
}
```
These are the functions in MyCharacter.cpp that the se Inputs are then binded too. 

```
void AMyCharacter::NewInput() //this is the input that it calls to do
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Pressed Input!!");

}
```
This one simply gets on on Screen Debug message upon being pressed.


```
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
```
This one is the player movement (Ignore the "Forward Direction" variable, it doesnt work), it calls for an InputVector of the players movement, as well as calling the players rotation. With this its able to create a variable "Right Direction" that gets the players rotation and then their Unit Axis on the X Axis.

In MyCharacter.h is where I set all the functions to exist, as well as for them to be visible and editable in the Blueprint Player. 

```
protected:

	UPROPERTY(EditAnywhere, Category =  "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	class UInputAction* TestAction;

	UPROPERTY(EditAnywhere, Category = "Enhanced Input")
	class UInputAction* MoveAction;

	void NewInput();

	void MoveForward(const FInputActionValue& InputValue);
```
In the Category of "Enhanced Input" in the player blueprints, it calls for an InputMapping Context and the two Inputs I created of the calling a debug message as well as moving left and right, as well as creating the two input functions for them to exist. Within the Player Blueprint you can then set these inputs for the player to recognise them. 

![The Player Blueprint](image.png)

Here I set the Input Mapping to the Mapping with our inputs, the Test Action to our debug message and the Move action to moving left and right. 

Lastly in our GameMode Blueprint, we change the default pawn class to the Player Blueprint with the inputs, as well as change the world settings to use this Game mode and place in our player. 

![The Gamemode](image-1.png)

Example Gif of this code working:

![The Input](Input.gif)

To allow this to easily work with Gamepad, I would just need to bind the Gamepad buttons into the Input Mapping Context, where I initally bind the buttons on the keyboard to this inputs.