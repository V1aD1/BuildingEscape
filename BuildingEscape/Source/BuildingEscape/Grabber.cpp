// Vlad Baderca 2018

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Classes/Components/PrimitiveComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return;  }
	if (PhysicsHandle->GrabbedComponent) 
	{
		//move object that we're holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}		
}

/// Look for attached physics handle
void UGrabber::FindPhysicsHandleComponent() {

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	//physics hande has been found
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Physics handle component was expected in %s!"), *GetOwner()->GetName());
	}
}

///Look for attacched input component (only instantiates at run time)
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}

	else {
		UE_LOG(LogTemp, Error, TEXT("Input component was expected in %s!"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	//try and reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	//if we hit something then attach a physics handle
	if (!PhysicsHandle) { return; }
	if (ActorHit) {
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation());
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///setup query params
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//line trace (ray cast) out to reach distance
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	))
	{
		AActor* actorHit = HitResult.GetActor();
		UE_LOG(LogTemp, Warning, TEXT("View Point ray cast is colliding with %s"), *(actorHit->GetName()))
	}

	return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
	// Get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd() {
	// Get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}
