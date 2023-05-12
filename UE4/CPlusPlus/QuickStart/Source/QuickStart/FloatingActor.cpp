// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"


// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bAutoMove = true;
	MoveRate = 20.0f;
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bAutoMove) return;

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime);
	NewLocation.Z += DeltaHeight * MoveRate; // 把高度以20的系数进行缩放
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
	
}

