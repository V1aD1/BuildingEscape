// Vlad Baderca 2018

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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

	//if physics handle is attached
		//move object that we're holding
}

/// Look for attached physics handle
void UGrabber::FindPhysicsHandleComponent() {

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();


	//physics hande has been found
	if (PhysicsHandle) {

	}

	//physics handle hasn't been included!!
	else {
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
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed!"));



	//try and reach any actors with physics body collision channe set
	GetFirstPhysicsBodyInReach();


	//if we hit something then attach a physics handle

	//todo attach physics handle


}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released!"));

	// todo release physics handle


}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Get player view point
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	///setup query params
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//line trace (ray cast) out to reach distance
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	))
	{

		///see what we hit
		AActor* actorHit = Hit.GetActor();

		UE_LOG(LogTemp, Warning, TEXT("View Point ray cast is colliding with %s"), *(actorHit->GetName()))
	}

	return Hit;
}


