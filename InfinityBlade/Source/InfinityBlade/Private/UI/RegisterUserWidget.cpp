// Fill out your copyright notice in the Description page of Project Settings.

#include "RegisterUserWidget.h"

/** 控件创建完成后初始化方法 */
bool URegisterUserWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	/** 初始化返回按钮 */
	BackBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Back")));
	/** 初始化昵称输入框 */
	NicknameInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Nickname")));
	/** 初始化密码输入框 */
	PasswordInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_Password")));
	/** 初始化确认密码输入框 */
	RePasswordInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_RePassword")));
	/** 初始化注册按钮 */
	RegisterBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Register")));
	/** 注册按钮的点击事件 */
	RegisterBtn->OnClicked.AddDynamic(this, &URegisterUserWidget::RegisterBtnOnClickedEvent);
	/** 初始化加载框 */
	CircularThrobber = Cast<UCircularThrobber>(GetWidgetFromName("CircularThrobber_Loading"));
	/** 初始化信息提示框 */
	MessageUserWidget = Cast<UMessageUserWidget>(GetWidgetFromName("BP_MessageUserWidget"));

	return true;
}

/** 注册账号按钮点击事件 */
void URegisterUserWidget::RegisterBtnOnClickedEvent()
{
	/** 获取昵称 */
	FString Nickname = NicknameInput->GetText().ToString();
	/** 获取密码 */
	FString Password = PasswordInput->GetText().ToString();
	/** 获取确认密码 */
	FString RePassword = RePasswordInput->GetText().ToString();

	/** 昵称的长度是否合法2-6 */
	if (Nickname.Len() < 2 || Nickname.Len() > 6)
	{
		/** 昵称长度是否合法 */
		MessageUserWidget->SetVisibility(ESlateVisibility::Visible);
		MessageUserWidget->MsgBlock->SetText(FText::FromString("NickName Is Not Right"));
		return;
	}
	/** 两次输入的密码是否一致 */
	if (!Password.Equals(RePassword))
	{
		/** 密码是否一致 */
		MessageUserWidget->SetVisibility(ESlateVisibility::Visible);
		MessageUserWidget->MsgBlock->SetText(FText::FromString("Second Password Is Not Same"));
		return;
	}
	/** 显示加载框 */
	CircularThrobber->SetVisibility(ESlateVisibility::Visible);
	/** 设置注册按钮不可用 */
	RegisterBtn->SetIsEnabled(false);
	/** 进行账号注册 */
	AccountRegisterFromServer(Nickname, Password);
}

/** 账号注册方法 */
void URegisterUserWidget::AccountRegisterFromServer(FString& Nickname, FString& Password)
{
	/** 创建要提交的Json字符串 */
	FString RegisterInfo;
	/** 创建共享Json写入器 */
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&RegisterInfo);
	/** 开始写入数据 */
	JsonWriter->WriteObjectStart();
	/** 写入昵称到Json */
	JsonWriter->WriteValue("nickname", Nickname);
	/** 写入密码到Json */
	JsonWriter->WriteValue("password", Password);
	/** 关闭Json写入 */
	JsonWriter->WriteObjectEnd();
	/** 关闭Json写入器 */
	JsonWriter->Close();

	/** 创建HTTP请求 */
	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	/** 设置请求方式 */
	HttpRequest->SetVerb("POST");
	/** 设置请求头 */
	HttpRequest->SetHeader("Content-Type", "application/json;charset=utf-8");
	/** 设置请求的url */
	HttpRequest->SetURL("http://localhost:7900/user/register-user");
	/** 设置上传的数据 */
	HttpRequest->SetContentAsString(RegisterInfo);
	/** 设置请求成功后委托方法 */
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &URegisterUserWidget::RequestComplete);
	/** 请求服务器 */
	HttpRequest->ProcessRequest();

}

/** 请求响应方法 */
void URegisterUserWidget::RequestComplete(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess)
{
	/** 隐藏加载框 */
	CircularThrobber->SetVisibility(ESlateVisibility::Hidden);
	/** 设置注册按钮可用 */
	RegisterBtn->SetIsEnabled(true);
	/** 判断响应状态是否正常 */
	if (!EHttpResponseCodes::IsOk(ResponsePtr->GetResponseCode()))
	{
		return;
	}
	/** 获取返回的值 */
	FString Data = ResponsePtr->GetContentAsString();
	/** 创建一个Json对象 */
	TSharedPtr<FJsonObject> JsonObject;
	/** 创建Json解析器 */
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Data);
	/** Json反序列化 */
	bool bIsParse = FJsonSerializer::Deserialize(JsonReader, JsonObject);
	/** 判断是否解析成功 */
	if (bIsParse)
	{
		/** 解析服务器返回的信息 */
		FString Msg = JsonObject->GetStringField("msg");
		/** 显示提示信息 */
		MessageUserWidget->SetVisibility(ESlateVisibility::Visible);
		MessageUserWidget->MsgBlock->SetText(FText::FromString(Msg));
	}
}