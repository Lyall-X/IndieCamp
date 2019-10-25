// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "ItemInfo.generated.h"

UENUM(BlueprintType)
enum class EPickupInfoType:uint8
{
	HP UMETA(DisplayName = "HP"),
	MP UMETA(DisplayName = "MP")
};

USTRUCT(BlueprintType)
struct FPickupInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		uint8 ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		EPickupInfoType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		float Num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		UTexture2D* Pic;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
		FText Desc;
};
