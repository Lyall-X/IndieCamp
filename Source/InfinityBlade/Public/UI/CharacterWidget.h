// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "CharacterWidget.generated.h"

/**
 * 人物角色信息的UI
 */
UCLASS()
class INFINITYBLADE_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** 关闭按钮 */
	UPROPERTY()
		UButton* BtnClose;
	/** 背包滚动盒 */
	UPROPERTY()
		UScrollBox* ScrollBox;
public:
	/** 重写按钮初始化方法 */
	virtual bool Initialize() override;
	/** 关闭按钮点击事件 */
	UFUNCTION()
		void CloseBtnOnClickedEvent();
};
