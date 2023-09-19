// Copyright Tornado Entertainment Ltd. All rights reserved.


#include "NotificationContainer.h"

#include "NotificationWidget.h"
#include "Components/VerticalBox.h"
#include "OffRocksUI/GameUISystem.h"

void UNotificationContainer::AddNotification(TSoftClassPtr<UNotificationWidget> inBPWidgetClass, ENotificationLocation inLocation, FText inDisplayText, float inTimeToShow)
{
	UClass* widgetClass = inBPWidgetClass.LoadSynchronous();
	UNotificationWidget* widget = CreateWidget<UNotificationWidget>(GetWorld(), widgetClass);
	switch(inLocation)
	{
		case ENotificationLocation::Screen_TL:
			NotificationContainerTopLeft->AddChildToVerticalBox(widget);
			break;
		case ENotificationLocation::Screen_BC:
			NotificationContainerBottomCenter->AddChildToVerticalBox(widget);
			break;
		default:
			break;
	}
	widget->ShowNotification(inDisplayText);
	widget->m_WidgetRemovedDelegate.AddUObject(this, &UNotificationContainer::OnNotificationRemoved);
	m_NotificationsAlive.Add(widget);

	if (inTimeToShow > 0)
	{
		FTimerHandle notHandle;
		GetWorld()->GetTimerManager().SetTimer(notHandle, widget, &UNotificationWidget::RemoveNotification, inTimeToShow);
	}
}

void UNotificationContainer::OnNotificationRemoved(UNotificationWidget* inRemovedWidget)
{
	m_NotificationsAlive.Remove(inRemovedWidget);
	inRemovedWidget->m_WidgetRemovedDelegate.RemoveAll(this);
}


TSet<TWeakObjectPtr<UNotificationWidget>> UNotificationContainer::GetCurrentNotifications()
{
	for (TWeakObjectPtr<UNotificationWidget> widget : m_NotificationsAlive)
	{
		if (!widget.IsValid())
		{
			m_NotificationsAlive.Remove(widget);
		}
	}

	return m_NotificationsAlive;
}
