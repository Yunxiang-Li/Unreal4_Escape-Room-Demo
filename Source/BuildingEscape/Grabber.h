// Yunxiang Li

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// A float to increase the player's view line.
	float mReach{100.f};
	// Initialize a pointer to a UPhysicsHandleComponent object.
	UPROPERTY(EditAnywhere, DisplayName = "PhysicsHandle")
	UPhysicsHandleComponent* mPhysicsHandle{nullptr};
	// Initialize a pointer to a UInputComponent object.
	UPROPERTY(EditAnywhere, DisplayName = "InputComponent")
	UInputComponent* mInputComponent{nullptr};
	// A function to let player grab a specific object.
	void Grab();
	// A function to let player release a specific object.
	void Release();
	// Find current Actor's physics handle.
	void FindPhysicsHandle();
	// Set up current Actor's input component. 
	void SetInputComponent();
	// Find the first physics body which current actor can reach.
	FHitResult GetFirstPhysicsBodyInReach() const;
	// Return the player view vector from the origin.
	FVector GetPlayerViewReach() const;
	// Get player's world position.
	FVector GetPlayerWorldPos() const;
};
