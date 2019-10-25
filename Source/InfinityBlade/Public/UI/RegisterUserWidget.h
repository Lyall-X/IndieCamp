// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/CircularThrobber.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"
#include "UI/MessageUserWidget.h"
#include "RegisterUserWidget.generated.h"

/**
 * 游戏注册界面UI
 */
UCLASS()
class INFINITYBLADE_API URegisterUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/** 返回上层按钮 */
	UPROPERTY()
		UButton* BackBtn;
	/** 昵称输入框 */
	UPROPERTY()
		UEditableTextBox* NicknameInput;
	/** 密码输入框 */
	UPROPERTY()
		UEditableTextBox* PasswordInput;
	/** 确认密码输入框 */
	UPROPERTY()
		UEditableTextBox* RePasswordInput;
	/** 注册按钮 */
	UPROPERTY()
		UButton* RegisterBtn;

	/** 加载框 */
	UPROPERTY()
		UCircularThrobber* CircularThrobber;
	/** 提示框UI */
	UPROPERTY()
		UMessageUserWidget* MessageUserWidget;

public:
	/** 控件创建完成后初始化方法 */
	virtual bool Initialize() override;
	/** 注册账号按钮点击事件 */
	UFUNCTION()
		void RegisterBtnOnClickedEvent();
	/** 账号注册方法 */
	void AccountRegisterFromServer(FString& Nickname, FString& Password);
	/** 请求响应方法 */
	void RequestComplete(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess);
};
