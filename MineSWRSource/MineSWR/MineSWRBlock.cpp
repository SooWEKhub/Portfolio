// Copyright Piotr Sowka, 2022

#include "MineSWRBlock.h"
#include "MineSWRBlockGrid.h"
#include "MineSWRPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "MineSWR.h"
#include "Materials/MaterialInstance.h"

AMineSWRBlock::AMineSWRBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> RedMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> GreenMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial"))
			, RedMaterial(TEXT("/Game/Puzzle/Meshes/RedMaterial.RedMaterial"))
			, GreenMaterial(TEXT("/Game/Puzzle/Meshes/GreenMaterial.GreenMaterial"))
			, OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &AMineSWRBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &AMineSWRBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	RedMaterial = ConstructorStatics.RedMaterial.Get();
	GreenMaterial = ConstructorStatics.GreenMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
}

void AMineSWRBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	int field = this->BlockNb;
	//GEngine->AddOnScreenDebugMessage(-1, 25.0f, FColor::Cyan, FString::FromInt(field));
	if (DiffLevel == 1)
	{
		kol = 10;
	}

	if (DiffLevel == 2)
	{
		kol = 40;
	}

	if (DiffLevel == 3)
	{
		kol = 100;
	}

	if (DiffLevel == 4)
	{
		kol = 500;
	}

	y = field / kol;
	x = field % kol;
	//GEngine->AddOnScreenDebugMessage(-1, 25.0f, FColor::Cyan, FString::FromInt(x) + " " + FString::FromInt(y));
	OwningGrid->WebSocket->Send("open " + FString::FromInt(x) + " " + FString::FromInt(y));
	OwningGrid->WebSocket->Send("map");
	HandleClicked();	
}


void AMineSWRBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void AMineSWRBlock::HandleClicked()
{
	
	// Check we are not already active
		if (!bIsActive)
	{
		bIsActive = true;

	}

			OwningGrid->AddScore();
			

			FString BlockName = this->GetName();
			//GEngine->AddOnScreenDebugMessage(-1, 25.0f, FColor::Yellow, *BlockName.Mid(13, BlockName.Len() - 13));
				BlockMesh->SetMaterial(0, RedMaterial);

}

void AMineSWRBlock::Highlight(bool bOn)
{
	// Do not highlight if the block has already been activated.
	if (bIsActive)
	{
		return;
	}

	if (bOn)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, BlueMaterial);
	}
}
