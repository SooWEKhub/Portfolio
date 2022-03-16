// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneratorLabiryntu.generated.h"

UCLASS()
class LABIRYNT_API AGeneratorLabiryntu : public AActor
{
	GENERATED_BODY()
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UStaticMesh*> pokoj;
	//class UStaticMesh* pokoj;
	
public:	
	// Sets default values for this actor's properties
	AGeneratorLabiryntu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

};
