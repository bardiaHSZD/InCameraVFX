// Fill out your copyright notice in the Description page of Project Settings.


#include "DN_BeamActor.h"

// Sets default values
ADN_BeamActor::ADN_BeamActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADN_BeamActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADN_BeamActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

