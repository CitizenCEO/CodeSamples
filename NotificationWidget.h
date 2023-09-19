// Copyright Tornado Entertainment Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotificationWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWidgetRemovedSignature, UNotificationWidget*)


class UTextBlock;
UCLASS()
class OFFROCKSUI_API UNotificationWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShowNotificationAnimation;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ShownMessageTextBlock;

	bool bRemoveRequested = false;
	bool bHidden = false;

	virtual void OnAnimationFinishedPlaying(UUMGSequencePlayer& Player) override;
	void HideNotification();

public:
	void ShowNotification(FText inShownText);
	void RemoveNotification();

	FOnWidgetRemovedSignature m_WidgetRemovedDelegate;
};
