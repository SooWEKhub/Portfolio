// Copyright Piotr Sowka, 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IWebSocket.h"
#include "MineSWRBlock.h"
#include "MineSWRBlockGrid.generated.h"


/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class AMineSWRBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;

public:
	AMineSWRBlockGrid();

	/** How many blocks have been clicked */
	int32 Score;
	TArray<AMineSWRBlock> Blocks;

	/** Number of blocks along each side of grid */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 SizeX;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 SizeY;

	/** Spacing of blocks */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

	TSharedPtr<IWebSocket> WebSocket;

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

public:

	/** Handle the block being clicked */
	void AddScore();

	UFUNCTION()
	void OnSocketReceiveMessage(const FString& Message);

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns ScoreText subobject **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }
};



