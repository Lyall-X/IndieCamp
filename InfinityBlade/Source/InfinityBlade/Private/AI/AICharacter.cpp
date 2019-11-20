// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"

/** 构造方法 */
AAICharacter::AAICharacter()
{
	/** 初始化UI控件 */
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetMesh());
}

/** 游戏开始调用的方法 */
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	/** 初始化血条 */
	HPBar = Cast<UProgressBar>(WidgetComponent->GetUserWidgetObject()->GetWidgetFromName(TEXT("AIHPBar")));
	/** 初始化当前血量 */
	CurrentHP = TotalHP;
	/** 初始化当前的血量UI */
	HPBar->SetPercent(CurrentHP / TotalHP);
}


/** 重写收到伤害的方法 */
float AAICharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	/** 当前血量减少 */
	CurrentHP -= Damage;
	/** 更新UI */
	HPBar->SetPercent(CurrentHP / TotalHP);

	return Damage;
}

