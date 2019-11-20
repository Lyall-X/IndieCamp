 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "AICharacter.generated.h"

/**
 * AI怪物类
 */
UCLASS()
class INFINITYBLADE_API AAICharacter : public ACharacter
{
	GENERATED_BODY()
public:
	/** UI组件 */
	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* WidgetComponent;
	/** 血量 */
	UPROPERTY(EditAnywhere, Category = "State")
		float TotalHP;
	/** 当前血量 */
	float CurrentHP;
	/** 是否死亡 */
	bool bIsDead;
	/** 血条Widget */
	UPROPERTY()
		UProgressBar* HPBar;

public:
	/** 构造方法 */
	AAICharacter();

protected:
	/** 游戏开始调用的方法 */
	virtual void BeginPlay() override;
	/** 重写收到伤害的方法 */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
