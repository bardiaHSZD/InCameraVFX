// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Remote Sensing")
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Remote Sensing")
		UStaticMeshComponent* StartPointMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Remote Sensing")
		UStaticMeshComponent* EndPointMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Remote Sensing")
		UStaticMeshComponent* LocatorMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Remote Sensing")
		USplineComponent* SplineComponentBeam;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Remote Sensing")
		USplineMeshComponent* SplineMeshComponentBeam;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Remote Sensing")
		UArrowComponent* ArrowComponentBeam;

	// Avoids the camera attached to the character to stay behind a wall or any object
	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		USpringArmComponent* SpringArmComponent;

	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		UCameraComponent* CameraComponent;
	
	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		UFloatingPawnMovement* MovementComponent;

	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		float BaseTurnRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		bool DrawTraceLine = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		bool DisplayTraceLineMessage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		bool LiveRayCast = false;

	UPROPERTY(visibleAnywhere)
		AActor* RayCastHitResult;
	
	UPROPERTY(visibleAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		float BaseLookUpRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		FVector SplineEndPoint = FVector(0.0f,0.0f,0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		AActor* SplineEndMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		float StartRadius = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		float EndRadius = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Remote Sensing")
		float BeamRadius = 1.0f;

	UFUNCTION(BlueprintCallable, Category = "Remote Sensing")
		void AttachEndTo(const FVector& position);

	UFUNCTION(CallInEditor, Category = "Remote Sensing")
		void AttachEndPoint();
	
	UFUNCTION(CallInEditor, Category = "Remote Sensing")
		void AttachEndMesh();
	
	UFUNCTION(CallInEditor, Category = "Remote Sensing")
		void SetStartRadius();

	UFUNCTION(CallInEditor, Category = "Remote Sensing")
		void SetEndRadius();
	
	UFUNCTION(CallInEditor, Category = "Remote Sensing")
		void SetBeamRadius();

	void UpdateSplineBeam(const FVector& SplineEndPoint);
	void UpdateSplineBeamMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void LogBeforeAttach() const;
	void LogAfterAttach() const;
	void LogReport(FString FState) const;
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void TurnRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void TurnRightRate(float AxisValue);
	void AddRayCast();

	float StartLineTraceMultiplier = 500.0f;
	float EndLineTraceMultiplier = 1000.0f;
	AActor* LastRayCastHitResult = nullptr;




public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
