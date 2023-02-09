// Fill out your copyright notice in the Description page of Project Settings.


#include "DN_ProfessionalLaserBeamPawn.h"


void ADN_ProfessionalLaserBeamPawn::RayCastEndPoint()
{
	AttachEndTo(SplineEndPoint);
	EndPointMesh->SetWorldLocation(SplineEndPoint);
	LiveRayCast = true;
	AddRayCast();
}