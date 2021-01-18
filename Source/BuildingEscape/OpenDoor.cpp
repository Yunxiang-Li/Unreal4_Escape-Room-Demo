
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
// For UWorld::GetWorld method
#include "Engine/World.h"
// For player controller
#include "GameFramework/PlayerController.h"
// To get An actor's mass.
#include "Components/PrimitiveComponent.h"
// To use door audio.
#include "Components/AudioComponent.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Set the initial yaw value of the door.
	mInitialYaw = GetOwner() -> GetActorRotation().Yaw;
	// Set the current yaw value the same as the initial yaw value.
	mCurrentYaw = mInitialYaw;
	// Set the target yaw value to be 90 degrees according to the initial yaw value.
	mTargetYaw += mInitialYaw;
	// Set the audio component of the door.
	SetAudioComponent();
	// Check if mPressurePlate pointer is set or not.
	SetPressurePlate();
}

/**
 * @brief Check if the pressure plate of the door is set properly.
 * 
 */
void UOpenDoor::SetPressurePlate() {
	if (!mPressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component but no pressure plate was set before!"), *(GetOwner() -> GetName()));
	}
}

/**
 * @brief Set the audio component of the door properly.
 * 
 */
void UOpenDoor::SetAudioComponent() {
	mAudioComponent = GetOwner() -> FindComponentByClass<UAudioComponent>();
	// Check if mAudioComponent is set up well.
	if (!mAudioComponent) {
		UE_LOG(LogTemp, Error, TEXT("%s missing an audio component"), *(GetOwner() -> GetName()));
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the player enters the trigger zone.
	if (mPressurePlate && TotalMassOfActor() > mOpenDoorMass) {
		// Open the door.
		OpenDoor(DeltaTime);
		// Set the door opened time per frame.
		mDoorOpenedTime = GetWorld() -> GetTimeSeconds();
	}
	else {
		// If current time minus door opened time is beyond the time limit, then close the door.
		if (GetWorld() -> GetTimeSeconds() - mDoorOpenedTime >= mDoorCloseDelay) {
			CloseDoor(DeltaTime);
		}
	}
}

/**
 * @brief Open the door in the speed according to the Delta time and play the audio.
 * 
 * @param DeltaTime A float indicates the delta time between each two frames.
 */
void UOpenDoor::OpenDoor(float DeltaTime) {
	// Get each frame's door rotator.
	FRotator doorRotator = GetOwner() -> GetActorRotation();
	// Use FInterpTo function to update each frame's yaw value of the door.
	mCurrentYaw  = FMath::FInterpTo(mCurrentYaw, mTargetYaw, DeltaTime, DeltaTime * mDoorOpenSpeed);
	// Assign current yaw value to each frame's door rotator's yaw value.
	doorRotator.Yaw = mCurrentYaw;
	// Set door rotation in each frame.
	GetOwner() -> SetActorRotation(doorRotator);
	// If open door sound is not played.
	if (!mOpenDoorSoundPlayed) {
		// Play the open door sound
		mAudioComponent -> Play();
		// Set two bools.
		mOpenDoorSoundPlayed = true;
		mCloseDoorSoundPlayed = false;
	}
		
}

/**
 * @brief Close the door in the speed according to the Delta time and play the audio.
 * 
 * @param DeltaTime A float indicates the delta time between each two frames.
 */
void UOpenDoor::CloseDoor(float DeltaTime) {
	// Get each frame's door rotator.
	FRotator doorRotator = GetOwner() -> GetActorRotation();
	// Use FInterpTo function to update each frame's yaw value of the door.
	mCurrentYaw  = FMath::FInterpTo(mCurrentYaw, mInitialYaw, DeltaTime, DeltaTime * mDoorCloseSpeed);
	// Assign current yaw value to each frame's door rotator's yaw value.
	doorRotator.Yaw = mCurrentYaw;
	// Set door rotation in each frame.
	GetOwner() -> SetActorRotation(doorRotator);

	// If close door sound is not played.
	if (!mCloseDoorSoundPlayed) {
		// Play the open door sound
		mAudioComponent -> Play();
		// Set two bools.
		mCloseDoorSoundPlayed = true;
		mOpenDoorSoundPlayed = false;
	}
}

/**
 * @brief Get total mass of actors in the pressure plate area.
 * 
 * @return float a float indicates the total mass.
 */
float UOpenDoor::TotalMassOfActor() const {
	float totalMass{0.f};

	// Store all overlapping actors.
	TArray<AActor*> overlappingActors;
	mPressurePlate -> GetOverlappingActors(OUT overlappingActors);

	// Add all actor's mass together.
	for (AActor* actorPtr : overlappingActors) {
		totalMass += actorPtr -> FindComponentByClass<UPrimitiveComponent>() -> GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s is on the pressure plate!"), *(actorPtr -> GetName()));
	}

	return totalMass;
}

