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

};
