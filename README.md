# Unreal Interaction System

Within the MyCharacter.cpp I create the Line trace specifically within AMyCharacter::Tick so that the Line trace is ran every single tick. Inside the MyCharacter.h, the actor needs a library to have the line trace work within the actor.

```
#include "Kismet/KismetSystemLibrary.h"
```

 For the Line Trace to run I had to create a camera component for the player to have a spot for the Line trace to have a starting point, as well as which direction for the Line trace to point towards from the Camera (which is forwards from the Camera). The line trace also needs a vector end so that the Line trace doesn't go on forever along with the vector start and the vector forward, as well as the hit result of what the line trace overlaps with. 

```
FVector Start = Camera->GetComponentLocation();

FVector Forward = Camera->GetForwardVector();

FVector End = ((Forward * 1000.0f) + Start);

FHitResult outHit;
```
The Camera Component in MyCharacter.h
```
UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;
```

Next I need to declare what channels I allow for the line trace to interact with into an Array, through an Object Type Query, which is any static object within the Unreal Engine.

```
TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
```
I also added the ability for the Line Trace to recognise the player, but instead of returning a response from being interacted with, the Line trace ignores the player also knowns as GetOwner, so that if there was to be another player in the world the Line trace can interact with them, but not the player that the line trace originates from. 

```
TArray<AActor*> ignore;
	ignore.Add(GetOwner());
```

Then finally for the Line trace, I need the boolean result checking if the Line trace is infact overlapping over an object or not, with the Kismet Library fromMyCharacter.h in use, using all the parameters I wrote out of where the start and end of the line trace is, what objects it can interact with, the ignore list which is the player, for the Line trace to draw a line for one frame, it's outhit and also the boolean result to be true for ignore self (ignoring the player). 

```
bool result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, TraceObjectTypes, false, ignore, EDrawDebugTrace::ForOneFrame, OUT outHit, true);
```

With the Line trace working I can create an if statement that if the Line Trace is overlapping something, depending on what it's overlapping it displays the name of that static mesh in the debug message. Which shall be replaced to be put into the interactable interface soon instead. 

```
if (result) {
		FString f = FString(outHit.GetActor()->GetName());

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, f);
	}
```

https://www.youtube.com/watch?v=4IbuUT6Tyj8
https://www.youtube.com/watch?v=2f17A0DXO4Q

GOOD LUCK GANG