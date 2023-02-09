// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DN_LaserBeamPawn.h"
#include "DN_ProfessionalLaserBeamPawn.generated.h"

/**
 * 
 */
UCLASS()
class INCAMERAFX_API ADN_ProfessionalLaserBeamPawn : public ADN_LaserBeamPawn
{
	GENERATED_BODY()


	UFUNCTION(CallInEditor, Category = "Remote Sensing")
	void RayCastEndPoint();
	
};
