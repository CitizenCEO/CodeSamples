// Copyright Tornado Entertainment Ltd. All rights reserved.

#include "NotificationWidget.h"

#include "Animation/UMGSequencePlayer.h"
#include "Components/TextBlock.h"


void UNotificationWidget::OnAnimationFinishedPlaying(UUMGSequencePlayer& Player)
{
	Super::OnAnimationFinishedPlaying(Player);

	bHidden = !Player.IsPlayingForward();

	if (bRemoveRequested)
	{
		RemoveNotification();
	}
}

void UNotificationWidget::HideNotification()
{
	if (!IsAnimationPlaying(ShowNotificationAnimation))
		PlayAnimation(ShowNotificationAnimation, 0, 1, EUMGSequencePlayMode::Reverse);
}

void UNotificationWidget::ShowNotification(FText inShownText)
{
	ShownMessageTextBlock->SetText(inShownText);
	if (!IsAnimationPlaying(ShowNotificationAnimation))
		PlayAnimation(ShowNotificationAnimation, 0, 1, EUMGSequencePlayMode::Forward);
}

void UNotificationWidget::RemoveNotification()
{
	bRemoveRequested = true;

	if (bHidden)
	{
		m_WidgetRemovedDelegate.Broadcast(this);
		RemoveFromParent();
	}
	else
	{
		HideNotification();
	}
}
