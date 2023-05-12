// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/TextRenderComponent.h>

#include "Countdown.generated.h"

UCLASS()
class QUICKSTART_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//倒计时运行时长，按秒计
	UPROPERTY(EditAnywhere)
	int CountdownTime;
	UTextRenderComponent* CountdownText;
	
	FTimerHandle CountdownTimerHandle;

	void UpdateTextDisplay();

	void AdvanceTimer();


	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished();
	virtual void CountdownHasFinished_Implementation();

	
};
