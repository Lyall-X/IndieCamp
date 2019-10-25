// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Pickup/ItemInfo.h"
#include "Pickup.generated.h"

/**
 * 拾取的物品
 */

UCLASS()
class INFINITYBLADE_API APickup : public AActor
{
	GENERATED_BODY()
	
public:
	/** 场景组件 */
	UPROPERTY(VisibleAnywhere)
		USceneComponent * SceneComponent;
	/** 碰撞胶囊体 */
	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CapsuleComponent;
	/** 网格模型组件 */
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* MeshComponent;
	/** 物品信息 */
	UPROPERTY(EditAnywhere, Category = "Property")
		FPickupInfo PickupInfo;
public:	
	/** 构造方法 */
	APickup();
	/** 物品碰撞方法 */
	UFUNCTION()
		void PickupOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult);

protected:
	/** 游戏开始调用的方法 */
	virtual void BeginPlay() override;
};
