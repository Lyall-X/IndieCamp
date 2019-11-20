// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MainUserWidget.generated.h"

/**
 * 主界面UI
 */
UCLASS()
class INFINITYBLADE_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** HP */
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* ProgressBar_HP;
	/** MP */
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* ProgressBar_MP;
	/** 攻击按钮 */
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Attack;

	/** 寒冰之石技能按钮 */
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_IceStone;
	/** 寒冰之石技能冷却进度条 */
	UPROPERTY(Meta = (BindWidget))
		UProgressBar* IceStoneCDBar;
	/** 寒冰之石技能冷却时间提示 */
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* IceStoneCDText;

	/** 恢复之术技能按钮 */
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Cure;

	/** 雷霆之光技能按钮 */
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Thunder;

	/** 无尽之刃技能按钮 */
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_XBlade;

};
