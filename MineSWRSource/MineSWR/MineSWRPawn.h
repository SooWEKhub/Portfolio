// Copyright Piotr Sowka, 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IWebSocket.h"
#include "MineSWRPawn.generated.h"

UCLASS(config=Game)
class AMineSWRPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

	float locX, locY, locX1, locY1;

	//AMineSWRBlockGrid Grid;

protected:
	void OnResetVR();
	void TriggerClick();
	void level1();
	void level2();
	void level3();
	void level4();
	void Up();
	void Down();
	void Left();
	void Right();
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class AMineSWRBlock* CurrentBlockFocus;
};
