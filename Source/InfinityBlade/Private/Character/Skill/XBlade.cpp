// Fill out your copyright notice in the Description page of Project Settings.

#include "XBlade.h"


/** 构造方法 */
AXBlade::AXBlade()
{
	/** 初始化场景组件 */
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	/** 设置父组件 */
	SceneComponent->SetupAttachment(RootComponent);
	/** 初始化胶囊体组件 */
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	/** 设置父组件 */
	CapsuleComponent->SetupAttachment(SceneComponent);
	/** 初始化粒子特效组件 */
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	/** 设置父组件 */
	ParticleSystemComponent->SetupAttachment(CapsuleComponent);
	/** 设置销毁时间 */
	InitialLifeSpan = 10.f;
}

/** 游戏开始调用的方法 */
void AXBlade::BeginPlay()
{
	Super::BeginPlay();
	
}

