
#include "Grabber.h"
// For UWorld::GetWorld method
#include "Engine/World.h"
// For player controller
#include "GameFramework/PlayerController.h"
// To draw the debug line.
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// Find current actor's physics handle.
	FindPhysicsHandle();
	// Set up the input component. 
	SetInputComponent();

}

/**
 * @brief Find current Actor's physics handle.
 * 
 */
void UGrabber::FindPhysicsHandle() {
	// Set the mPhysicsHandle.
	mPhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
	// Check if mPhysicsHandle is set up well.
	if (!mPhysicsHandle) {
		UE_LOG(LogTemp, Error, TEXT("No physics handle found for object %s"), *(GetOwner() -> GetName()));
	}
}

/**
 * @brief Set up current Actor's input component. 
 * 
 */
void UGrabber::SetInputComponent() {
	// Set the mPhysicsHandle.
	mInputComponent = GetOwner() -> FindComponentByClass<UInputComponent>();

	// Check if mInputComponent is set up well.
	if (mInputComponent) {
		// Bind the mInputComponent with grab function when player pressed E and right mouse key.
		mInputComponent -> BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		// Bind the mInputComponent with grab function when player pressed R key.
		mInputComponent -> BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

/**
 * @brief Help player grab a specific object.
 * 
 */
void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("GRAB"));
	// Get the hit result.
	FHitResult hit = GetFirstPhysicsBodyInReach();
	// Get the pointer to the actor that holds the hit component(the other object hit by player's view).
	AActor* hitActor = hit.GetActor();
	// If a hit occurs
	if (hitActor) {
		// Initialize an UPrimitiveComponent pointer to grab.
		UPrimitiveComponent* grabComponent{hit.GetComponent()};
		// Try to grab.
		mPhysicsHandle -> GrabComponentAtLocation(grabComponent, NAME_None, GetPlayerViewReach());
	}
}

/**
 * @brief Help player release a specific object.
 * 
 */
void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Release"));
	// Release the grabbed object.
	mPhysicsHandle -> ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check if the mPhysicsHandle is attached
	if (mPhysicsHandle -> GrabbedComponent) {
		// Set the object player is holding to player view reach position.
		mPhysicsHandle -> SetTargetLocation(GetPlayerViewReach());
	}
}

/**
 * @brief Return the player view vector from the origin.
 * 
 * @return FVector a FVector indicates the vector from the origin to the view point end.
 */
FVector UGrabber::GetPlayerViewReach() const {
	// Store two out arguments.
	FVector playerViewPointLocation;
	FRotator playerViewPointRotator;

	// Set them in each frame.
	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(OUT playerViewPointLocation,
																   OUT playerViewPointRotator);
	// Get the player view vector from the origin.															   
	return (playerViewPointLocation + playerViewPointRotator.Vector() * mReach);
}

/**
 * @brief Get player's world position.
 * 
 * @return FVector a FVector indicates the world position of the player.
 */
FVector UGrabber::GetPlayerWorldPos() const {
	// Initialize player's view point location and rotator.
	FVector playerViewPointLocation;
	FRotator playerViewPointRotator;

	// Set them in each frame.
	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(OUT playerViewPointLocation,
																   OUT playerViewPointRotator);
	return playerViewPointLocation;
}

/**
 * @brief Find the first physics body which current actor can reach.
 * 
 * @return FHitResult A FHitResult which indicates the hit player had with a physics body.
 */
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {

	// Initialize a FHitResult.
	FHitResult hit;
	// Initalize a FCollisionQueryParams, do not trace the player.
	FCollisionQueryParams traceParams(FName(TEXT("")), false, GetOwner());
	// Ray-cast to a certain distance.
	GetWorld() -> LineTraceSingleByObjectType(OUT hit, GetPlayerWorldPos(), GetPlayerViewReach(),
									          FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), traceParams);
	return hit;
}
