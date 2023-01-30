// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
//#include "CustomGameMode.h"


#include "DN_LaserBeamPawn.generated.h"

UCLASS()
class INCAMERAFX_API ADN_LaserBeamPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADN_LaserBeamPawn();

	UPROPERTY(BlueprintReadWrite)
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* StartPointMesh;

	UPROPERTY(BlueprintReadWrite)
		USplineComponent* SplineComponentBeam;
	
	UPROPERTY(BlueprintReadWrite)
		USplineMeshComponent* SplineMeshComponentBeam;

	UPROPERTY(BlueprintReadWrite)
		UArrowComponent* ArrowComponentBeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		FVector SplineEndPoint = FVector(0.0f,0.0f,0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		AActor* SplineEndMesh;

	UFUNCTION(CallInEditor, Category = "Remote Sensing")
		void AttachEndPoint();
	
	UFUNCTION(CallInEditor, Category = "Remote Sensing")
		void AttachEndMesh();
	
	void UpdateSplineBeam(const FVector& SplineEndPoint);
	void UpdateSplineBeamMesh();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
