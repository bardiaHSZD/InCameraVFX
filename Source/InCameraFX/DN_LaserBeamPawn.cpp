// Fill out your copyright notice in the Description page of Project Settings.


#include "DN_LaserBeamPawn.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ADN_LaserBeamPawn::ADN_LaserBeamPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Root"));
	LocatorMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Locator"));
	StartPointMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("StartingPointMesh"));
	SplineComponentBeam = CreateAbstractDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SplineMeshComponentBeam = CreateAbstractDefaultSubobject<USplineMeshComponent>(TEXT("SplineMesh"));
	ArrowComponentBeam = CreateAbstractDefaultSubobject<UArrowComponent>(TEXT("ArrowDirection"));
	EndPointMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("EndingPointMesh"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MovementComponent = CreateAbstractDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));



	// Attaching all of the components defined above to the root component, i.e. "RootComponent".
	LocatorMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	StartPointMesh->AttachToComponent(LocatorMesh, FAttachmentTransformRules::KeepRelativeTransform);
	SplineComponentBeam->AttachToComponent(LocatorMesh, FAttachmentTransformRules::KeepRelativeTransform);
	SplineMeshComponentBeam->AttachToComponent(SplineComponentBeam, FAttachmentTransformRules::KeepRelativeTransform);
	ArrowComponentBeam->AttachToComponent(LocatorMesh, FAttachmentTransformRules::KeepRelativeTransform);
	EndPointMesh->AttachToComponent(LocatorMesh, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	



	

	SpringArmComponent->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ADN_LaserBeamPawn::BeginPlay()
{
	Super::BeginPlay();

	
}

void ADN_LaserBeamPawn::LogBeforeAttach() const
{
	LogReport("Before Attach: ");
}

void ADN_LaserBeamPawn::LogAfterAttach() const
{
	LogReport("After Attach: ");
}

void ADN_LaserBeamPawn::LogReport(FString FState) const
{
	int32 SplineLastIndex = 1;
	ESplineCoordinateSpace::Type SplineMeshCoordinateSpace = ESplineCoordinateSpace::Local;
	FVector SplineEndLocation = SplineComponentBeam->GetLocationAtSplinePoint(SplineLastIndex, SplineMeshCoordinateSpace);
	FString StringSplineEndLocation = *SplineEndLocation.ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s Location of Ending Point is %s"), *FState, *StringSplineEndLocation);
}

void ADN_LaserBeamPawn::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;
	
	// Previously: //AddMovementInput(GetActorForwardVector(), value);
    // To change the orientation towards the camera direction:
	
	
	AddMovementInput(ControlRot.Vector(), Value);
}

void ADN_LaserBeamPawn::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	// Previously: // AddMovementInput(GetActorRightVector(), value);
	// To avoid moving around itself:
	// x = forward (red)
	// y = right (green)
	// z = up (blue)

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}

void ADN_LaserBeamPawn::AddRayCast()
{
	FVector StartLineTrace = GetActorLocation();
	FVector CameraForwardVector = CameraComponent->GetForwardVector();
	float StartLineTraceMultiplier = 100.0f;
	float EndLineTraceMultiplier = 1000.0f;
	StartLineTrace += 100.0f*CameraForwardVector;
	FVector EndLineTRace = StartLineTrace + EndLineTraceMultiplier*CameraForwardVector;
	FHitResult Hit;

	if (GetWorld())
	{
		bool ActorHit = GetWorld()->LineTraceSingleByChannel(Hit,StartLineTrace,EndLineTRace,ECC_Pawn,FCollisionQueryParams(),FCollisionResponseParams());
		DrawDebugLine(GetWorld(),StartLineTrace,EndLineTRace,FColor::Red,false,2.0f,0.0f,10.0f);
		if (ActorHit && Hit.GetActor())
		{
			GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red,Hit.GetActor()->GetFName().ToString());
		}
	}
}


void ADN_LaserBeamPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADN_LaserBeamPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADN_LaserBeamPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADN_LaserBeamPawn::MoveRight);
	
	//Yaw: Horizontal Rotation (left-right), 
	//Pitch: Vertical Rotation (up-down), 
	//Roll: Swing Rotation (airplane) 
	
	PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Cast", IE_Pressed, this, &ADN_LaserBeamPawn::AddRayCast);

}

void ADN_LaserBeamPawn::AttachEndTo(const FVector& Position)
{
	LogBeforeAttach();
	UpdateSplineBeam(Position);
	UpdateSplineBeamMesh();
	LogAfterAttach();
}

void ADN_LaserBeamPawn::AttachEndPoint()
{	
	AttachEndTo(SplineEndPoint);
	EndPointMesh->SetWorldLocation(SplineEndPoint);
}

void ADN_LaserBeamPawn::AttachEndMesh()
{
	if (SplineEndMesh != nullptr)
	{ 
		AttachEndTo(SplineEndMesh->GetActorLocation());
		EndPointMesh->SetWorldLocation(SplineEndMesh->GetActorLocation());
	}
}

void ADN_LaserBeamPawn::SetStartRadius()
{
	StartPointMesh->SetRelativeScale3D(StartRadius * FVector(1.0f,1.0f,1.0f));
}

void ADN_LaserBeamPawn::SetEndRadius()
{
	EndPointMesh->SetRelativeScale3D(EndRadius * FVector(1.0f, 1.0f, 1.0f));
}

void ADN_LaserBeamPawn::SetBeamRadius()
{
	SplineComponentBeam->SetRelativeScale3D(FVector(1.0f, BeamRadius, BeamRadius));
}

void ADN_LaserBeamPawn::UpdateSplineBeam(const FVector& SplineInLocationTarget)
{
	int32 StartSplinePointIndex = 0;
	int32 EndSplinePointIndex = 1;
	ESplineCoordinateSpace::Type SplineCoordinateSpace = ESplineCoordinateSpace::World;
	const FVector& SplineInLocation = SplineInLocationTarget;
	bool SplineUpdateSpline = true;
	SplineComponentBeam->SetLocationAtSplinePoint(EndSplinePointIndex, SplineInLocation,
		SplineCoordinateSpace, SplineUpdateSpline);
}

void ADN_LaserBeamPawn::UpdateSplineBeamMesh()
{
	int32 StartSplinePointIndex = 0;
	int32 EndSplinePointIndex = 1;
	ESplineCoordinateSpace::Type SplineMeshCoordinateSpace = ESplineCoordinateSpace::Local;
	FVector SplineMeshStartPos = SplineComponentBeam->GetLocationAtSplinePoint(StartSplinePointIndex, SplineMeshCoordinateSpace);
	FVector SplineStartTangent = SplineComponentBeam->GetLocationAtSplinePoint(StartSplinePointIndex, SplineMeshCoordinateSpace);
	FVector SplineEndPos = SplineComponentBeam->GetLocationAtSplinePoint(EndSplinePointIndex, SplineMeshCoordinateSpace);
	FVector SplineEndTangent = SplineComponentBeam->GetLocationAtSplinePoint(EndSplinePointIndex, SplineMeshCoordinateSpace);
	SplineMeshComponentBeam->SetStartAndEnd(SplineMeshStartPos, SplineStartTangent, SplineEndPos, SplineEndTangent);
}



