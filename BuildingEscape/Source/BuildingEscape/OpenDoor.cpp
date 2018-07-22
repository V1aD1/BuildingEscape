// Vlad Baderca 2018

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Classes/Components/PrimitiveComponent.h"
#include "Classes/Kismet/GameplayStatics.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate!!"), *GetOwner()->GetName());
	}

	if (TriggeringActors.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing triggering actors for pressure plate!!"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll trigger volume
	if (IsTriggeringActorOnPlate()) //todo remove hardcoded 50
	{
		OnOpen.Broadcast();
	}

	else {
		OnClose.Broadcast();
	}
}

//Returns true if a triggering actor (which ALWAYS includes the player actor)
//are on the pressure plate
bool UOpenDoor::IsTriggeringActorOnPlate()
{
	TArray<AActor*> OverLappingActors;

	if (!PressurePlate) { return false; }
	if (TriggeringActors.Num() == 0) { return false; }

	PressurePlate->GetOverlappingActors(OUT OverLappingActors);

	//iterate through them and calculate their mass
	for (const auto& Actor : OverLappingActors) {
		if (Actor == Player) { return true; }
		for (const auto& TriggeringActor : TriggeringActors) {
			if (Actor == TriggeringActor) { return true; }
		}
	}

	return false;
}

