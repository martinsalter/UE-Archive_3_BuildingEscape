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
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(PhysicsHandle == nullptr){
		UE_LOG(LogTemp, Error, TEXT("Unable to find UPhysicsHandleComponent on %s"), *(GetOwner()->GetName()));
	}
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(InputComponent != nullptr){
		UE_LOG(LogTemp, Warning, TEXT("Found InputComponent"))
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
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
	DrawDebugLine(
		GetWorld(),
		LookPosition,
		GrabberLocation,
		FColor(255, 0, 0),
		false, 
		0.0f, 
		0.0f, 
		5.0f
		);

	// Raycast out to GrabberLocation
	FHitResult GrabberHitResult;
	bool bGrabberHit = GetWorld()->LineTraceSingleByObjectType(
		OUT GrabberHitResult,
		LookPosition,
		GrabberLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(false)
	);
	// See what we hit
	if (bGrabberHit)
	{
		AActor* ActorHit = GrabberHitResult.GetActor();
		UE_LOG(LogTemp, Warning, TEXT("Grabber is touching %s"), *(ActorHit->GetName()))
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"))
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"))
}
