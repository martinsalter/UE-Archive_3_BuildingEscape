// (c) Copright Martisan 2019.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If ActorThatOpens is overlapping trigger volume
	if(PressurePlate->IsOverlappingActor(ActorThatOpens)){
		OpenDoor();
		TimePPLastActivated = GetWorld()->GetTimeSeconds();		
	}
	if(GetWorld()->GetTimeSeconds()-TimePPLastActivated > DoorCloseDelay){
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor(){
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor(){
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}