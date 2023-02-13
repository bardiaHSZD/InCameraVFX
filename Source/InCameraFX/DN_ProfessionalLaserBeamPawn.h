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

protected:
	void AddRayCast();

public: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		float RayCastStart = DefaultRayCastStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		float RayCastEnd = DefaultRayCastEnd;

	UFUNCTION(CallInEditor, Category = "Remote Sensing")
		virtual void RayCastEndPoint();
	
};
