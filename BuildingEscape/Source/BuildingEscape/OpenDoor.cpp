// Vlad Baderca 2018

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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
}

void UOpenDoor::OpenDoor()
{
	//Find the owning actor
	AActor* Owner = GetOwner();

	//Create a rotator
	FRotator NewRotation = FRotator(0.0f, -60.0f, 00.0f);

	//set the door rotation
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll trigger volume
	//if the actor that opens is in the volume, then we open the door
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}
}

