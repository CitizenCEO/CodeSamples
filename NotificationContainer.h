// Copyright Tornado Entertainment Ltd. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotificationContainer.generated.h"

class UVerticalBox;
class UNotificationWidget;
enum ENotificationLocation;

UCLASS()
class OFFROCKSUI_API UNotificationContainer : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* NotificationContainerTopLeft;
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* NotificationContainerBottomCenter;
	TSet<TWeakObjectPtr<UNotificationWidget>> m_NotificationsAlive;

	void OnNotificationRemoved(UNotificationWidget* inRemovedWidget);
public:
	void AddNotification(TSoftClassPtr<UNotificationWidget> inBPWidgetClass, ENotificationLocation inLocation, FText inDisplayText, float inTimeToShow);
	TSet<TWeakObjectPtr<UNotificationWidget>> GetCurrentNotifications();
};
