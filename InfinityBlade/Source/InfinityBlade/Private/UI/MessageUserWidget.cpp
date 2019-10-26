// Fill out your copyright notice in the Description page of Project Settings.

#include "MessageUserWidget.h"

/** 控件创建后初始化方法 */
bool UMessageUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	/** 初始化关闭按钮 */
	CloseBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Close")));
	/** 设置关闭按钮的点击事件 */
	CloseBtn->OnClicked.AddDynamic(this, &UMessageUserWidget::CloseBtnOnClickedEvent);
	/** 提示信息框初始化 */
	MsgBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Msg")));

	return true;
}

/** 关闭按钮点击事件 */
void UMessageUserWidget::CloseBtnOnClickedEvent()
{
	/** 隐藏掉信息提示框 */
	this->SetVisibility(ESlateVisibility::Hidden);
}
