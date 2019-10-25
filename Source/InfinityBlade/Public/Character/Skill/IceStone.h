// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "IceStone.generated.h"

/**
 * 寒冰之石
 */
UCLASS()
class INFINITYBLADE_API AIceStone : public AActor
{
	GENERATED_BODY()
	
public:
	/** 粒子系统组件 */
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* ParticleSystemComponent;
	/** 胶囊体组件 */
	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CapsuleComponent;
	/** 子弹移动组件 */
	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* ProjectileMovementComponent;
	/** 爆炸粒子特效 */
	UPROPERTY(EditAnywhere, Category = "Particle")
		UParticleSystem* ExplodeParticle;
	/** 爆炸粒子声音 */
	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundBase* ExplodeSound;
public:	
	/** 构造方法 */
	AIceStone();
	/** 发射方法 */
	void Shoot(FVector Direction);
protected:
	/** 游戏开始调用的方法 */
	virtual void BeginPlay() override;
	/** 击中事件 */
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult);
};
