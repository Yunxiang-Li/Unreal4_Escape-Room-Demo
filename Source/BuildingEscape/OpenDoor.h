
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Open the door.
	void OpenDoor(float DeltaTime);
	// Close the door.
	void CloseDoor(float DeltaTime);
	// Get total mass of actors in the pressure plate area.
	float TotalMassOfActor() const;
	// Set the audio sound of the door
	void SetAudioComponent();
	// Check if the pressure plate of the door is set properly.
	void SetPressurePlate();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Initialization of z axis rotation value of the door.
	float mInitialYaw;
	// Current z axis rotation value of the door.
	float mCurrentYaw;
	// A float indicates how long door was under open condition.
	float mDoorOpenedTime{0.f};
	// A float indicates the time delay before closing the door.
	UPROPERTY(EditAnywhere, DisplayName = "Delay time before door close")
	float mDoorCloseDelay{0.9f};
	// A float indicates the door open speed.
	UPROPERTY(EditAnywhere, DisplayName = "Speed to open the door")
	float mDoorOpenSpeed{150.f};
	// A float indicates the door close speed.
	UPROPERTY(EditAnywhere, DisplayName = "Speed to close the door")
	float mDoorCloseSpeed{200.f};
	// Target z axis rotation value of the door.
	UPROPERTY(EditAnywhere, DisplayName = "Target door open angle")
	float mTargetYaw{90.f};
	// A pointer to a TriggerVolume object.
	UPROPERTY(EditAnywhere, DisplayName = "Invisible pressure plate")
	ATriggerVolume* mPressurePlate{nullptr};
	// A float indicates the total mass need to open the door.
	UPROPERTY(EditAnywhere, DisplayName = "Mass to open the door")
	float mOpenDoorMass{45.f};
	// A pointer to a AudioComponent which indicates the sound when door opens or closes.
	UPROPERTY(EditAnywhere, DisplayName = "Door open and close sound")
	UAudioComponent* mAudioComponent{nullptr};
	// A bool indicates that open door sound is played.
	bool mOpenDoorSoundPlayed{false};
	// A bool indicates times that close door sound is played.
	bool mCloseDoorSoundPlayed{true};
};
