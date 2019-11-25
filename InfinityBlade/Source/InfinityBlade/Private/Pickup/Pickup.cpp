// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Character/XCharacter.h"

/** 构造方法 */
APickup::APickup()
{
	/** 初始化场景组件 */
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	/** 初始化胶囊体组件 */
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::PickupOverlap);
	/** 初始化网格模型 */
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	/** 附着根组件 */
	SceneComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetupAttachment(SceneComponent);
	MeshComponent->SetupAttachment(CapsuleComponent);
}

/** 游戏开始调用的方法 */
void APickup::BeginPlay()
{
	Super::BeginPlay();

}

/** 物品碰撞方法 */
void APickup::PickupOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult)
{
	AXCharacter* Character = Cast<AXCharacter>(OtherActor);
	Character->PickupArray.Add(PickupInfo);
	Destroy();
}