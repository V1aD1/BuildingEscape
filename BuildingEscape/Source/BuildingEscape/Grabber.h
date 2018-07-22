// Vlad Baderca 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//how far ahead of the player can we reach in centimetres
	float Reach = 150.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	
	//ray cast and grab what's in rach
	void Grab();

	void Release();

	void FindPhysicsHandleComponent();

	//setup assumed attached input component
	void SetupInputComponent();

	//return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	//returns current start of reach line
	FVector GetReachLineStart();

	//returns current end of reach line
	FVector GetReachLineEnd();
};
