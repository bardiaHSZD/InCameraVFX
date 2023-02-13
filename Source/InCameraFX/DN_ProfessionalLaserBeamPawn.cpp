// Fill out your copyright notice in the Description page of Project Settings.


#include "DN_ProfessionalLaserBeamPawn.h"


void ADN_ProfessionalLaserBeamPawn::AddRayCast()
{
	FVector StartLineTrace = GetActorLocation();
	FVector CameraForwardVector = CameraComponent->GetForwardVector();

	StartLineTrace += RayCastStart * CameraForwardVector;
	FVector EndLineTRace = StartLineTrace + RayCastEnd * CameraForwardVector;
	FHitResult Hit;

	if (GetWorld())
	{
		bool ActorHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLineTrace, EndLineTRace, ECC_Visibility, FCollisionQueryParams(), FCollisionResponseParams());
		if (DrawTraceLine == true)
		{
			DrawDebugLine(GetWorld(), StartLineTrace, EndLineTRace, FColor::Red, false, 2.0f, 0.0f, 10.0f);
		}
		if (ActorHit && Hit.GetActor())
		{
			AActor* IdentifiedHitResult = Hit.GetActor();
			AttachHitResult(IdentifiedHitResult);
		}
		else
		{
			FreeFormEndTo(EndLineTRace);
		}
	}
	
}



void ADN_ProfessionalLaserBeamPawn::RayCastEndPoint()
{
	AttachEndTo(SplineEndPoint);
	EndPointMesh->SetWorldLocation(SplineEndPoint);
	LiveRayCast = true;
	AddRayCast();
}