// Fill out your copyright notice in the Description page of Project Settings.

#include "IceStone.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

/** 构造方法 */
AIceStone::AIceStone()
{
	/** 初始化胶囊体组件 */
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	/** 绑定碰撞事件 */
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AIceStone::OnOverlap);
	/** 设置父组件 */
	CapsuleComponent->SetupAttachment(RootComponent);
	/** 初始化系统粒子组件 */
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	/** 设置父组件 */
	ParticleSystemComponent->SetupAttachment(CapsuleComponent);
	/** 初始化子弹移动组件 */
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	/** 设置子弹移动组件更新的组件 */
	ProjectileMovementComponent->SetUpdatedComponent(CapsuleComponent);
	/** 设置子弹移动组件的速度 */
	ProjectileMovementComponent->InitialSpeed = 600.f;
	/** 设置寒冰之石生命周期 */
	InitialLifeSpan = 2.f;
}

/** 游戏开始调用的方法 */
void AIceStone::BeginPlay()
{
	Super::BeginPlay();

}

/** 发射方法 */
void AIceStone::Shoot(FVector Direction)
{
	/** 发射后的速度 */
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

/** 击中事件 */
void AIceStone::OnOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "IceStone...");
	if (OtherActor)
	{
		/** 对击中的AI产生伤害 */
		UGameplayStatics::ApplyPointDamage(OtherActor, 50.f, HitResult.ImpactPoint, HitResult, nullptr, this, nullptr);
		/** 产生爆炸粒子特效 */
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeParticle, OtherActor->GetActorLocation());
		/** 播放爆炸声音 */
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplodeSound, OtherActor->GetActorLocation());
		/** 隐藏粒子系统 */
		ParticleSystemComponent->SetVisibility(false);
	}
}
