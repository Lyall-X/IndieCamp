// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "XBlade.generated.h"
/**
 * 无尽之剑技能
 */
UCLASS()
class INFINITYBLADE_API AXBlade : public AActor
{
	GENERATED_BODY()
public:
	/** 场景组件 */
	UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneComponent;
	/** 粒子特效 */
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* ParticleSystemComponent;
	/** 碰撞体 */
	UPROPERTY(VisibleAnywhere)
		UCapsuleComponent* CapsuleComponent;

public:
	/** 构造方法 */
	AXBlade();

protected:
	/** 游戏开始调用的方法 */
	virtual void BeginPlay() override;

};
