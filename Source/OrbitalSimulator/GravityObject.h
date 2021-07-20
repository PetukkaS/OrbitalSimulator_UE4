// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Array.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "UObject/Class.h"

#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

#include "Math/Color.h"
#include "Math/Vector.h"
#include "GenericPlatform/GenericPlatformMath.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GravityObject.generated.h"

UCLASS()
class ORBITALSIMULATOR_API AGravityObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGravityObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector CurrentVelocity = FVector(0.f); // m/s

public:	

	// Mass in Earth Masses
	UPROPERTY(EditAnywhere)
	float Mass = 1.f;

	UPROPERTY(EditAnywhere)
	FString Name = "Default";

	UPROPERTY(EditAnywhere)
	FVector InitialVelocity = FVector(0.f); // m/s

	UPROPERTY(EditAnywhere)
	FVector RGB = FVector(0.f);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UpdatePosition(float DeltaTime);

	virtual void UpdateVelocity(float DeltaTime);

	virtual FVector Acceleration();

	virtual float GetMass();

	virtual FString GetName();

};
