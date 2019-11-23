// (c) Copright Martisan 2019.


#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get current direction and position of player viewpoint
	FVector LookPosition;
	FRotator LookDirection;
	PlayerController->GetPlayerViewPoint(OUT LookPosition, OUT LookDirection);

	// Log out to TEST
	// UE_LOG(LogTemp, Warning, TEXT("Grabber position %s, direction %s"), *LookPosition.ToString(), *LookDirection.ToString())

	FVector GrabberLocation = LookPosition + LookDirection.Vector() * Reach;

	// Visualise grabber direction and distance
	DrawDebugLine(GetWorld(),LookPosition,GrabberLocation,FColor(255, 0, 0),false,3.0f, 0.0f, 5.0f);


}

