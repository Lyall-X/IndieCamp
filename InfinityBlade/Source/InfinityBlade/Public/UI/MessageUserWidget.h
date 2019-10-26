// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "MessageUserWidget.generated.h"

/**
 * 提示框UI
 */
UCLASS()
class INFINITYBLADE_API UMessageUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** 关闭按钮 */
	UPROPERTY()
		UButton* CloseBtn;
	/** 提示信息 */
	UPROPERTY()
		UTextBlock* MsgBlock;
public:
	/** 控件创建后初始化方法 */
	virtual bool Initialize() override;
	/** 关闭按钮点击事件 */
	UFUNCTION()
		void CloseBtnOnClickedEvent();
};
