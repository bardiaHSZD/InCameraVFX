// Fill out your copyright notice in the Description page of Project Settings.


#include "DN_LaserBeamPawn.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ADN_LaserBeamPawn::ADN_LaserBeamPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StartPointMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("StartingPointMesh"));
	SplineComponentBeam = CreateAbstractDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SplineMeshComponentBeam = CreateAbstractDefaultSubobject<USplineMeshComponent>(TEXT("SplineMesh"));
	ArrowComponentBeam = CreateAbstractDefaultSubobject<UArrowComponent>(TEXT("ArrowDirection"));



	// Attaching all of the components defined above to the root component, i.e. "RootComponent".
	StartPointMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SplineComponentBeam->AttachToComponent(StartPointMesh, FAttachmentTransformRules::KeepRelativeTransform);
	SplineMeshComponentBeam->AttachToComponent(SplineComponentBeam, FAttachmentTransformRules::KeepRelativeTransform);
	ArrowComponentBeam->AttachToComponent(StartPointMesh, FAttachmentTransformRules::KeepRelativeTransform);



}

// Called when the game starts or when spawned
void ADN_LaserBeamPawn::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ADN_LaserBeamPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void ADN_LaserBeamPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADN_LaserBeamPawn::AttachEndPoint()
{	
	const FVector& SplineInLocation = SplineEndPoint;
	UpdateSplineBeam(SplineInLocation);
	UpdateSplineBeamMesh();
}

void ADN_LaserBeamPawn::AttachEndMesh()
{
	if (SplineEndMesh != nullptr)
	{
		const FVector& SplineInLocation = SplineEndMesh->GetActorLocation();
		UpdateSplineBeam(SplineInLocation);
		UpdateSplineBeamMesh();
	}
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



