// Written and owned by Lukasz Dziedziczak. Copywrite 2025


#include "Character/PlayerTutorialComponent.h"
#include "Character/PlayerCharacter.h"
#include "UI/SurvivalScifi_HUD.h"

// Sets default values for this component's properties
UPlayerTutorialComponent::UPlayerTutorialComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerTutorialComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentThreshhold = 0;
	
}


// Called every frame
void UPlayerTutorialComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerTutorialComponent::HasLooked(float LookAmount)
{
	if (ShowMouseMoveInfo)
	{
		CurrentThreshhold += LookAmount;

		if (CurrentThreshhold >= LookThreshhold)
		{
			CurrentThreshhold = 0;
			ShowMouseMoveInfo = false;
			ShowMovementInfo = true;

			GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
		}
	}
}

void UPlayerTutorialComponent::HasMovement(float MoveAmount)
{
	if (ShowMovementInfo)
	{
		CurrentThreshhold += MoveAmount;
		if (CurrentThreshhold >= LookThreshhold)
		{
			ShowMovementInfo = false;
			ShowJumpInfo = true;
			GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
		}
	}
}

void UPlayerTutorialComponent::HasJumped()
{
	if (ShowJumpInfo)
	{
		ShowJumpInfo = false;
		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}
}

void UPlayerTutorialComponent::ItemPickedUp()
{
	if (!SeenInventoryInfo && !ShowingAnyInfo())
	{
		SeenInventoryInfo = true;
		ShowInventoryInfo = true;

		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}
}

void UPlayerTutorialComponent::HasOpenedInventory()
{
	if (ShowInventoryInfo)
	{
		ShowInventoryInfo = false;
		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}
}

void UPlayerTutorialComponent::ItemAddedToSlot()
{
	if (!SeenSlotInfo && !ShowingAnyInfo())
	{
		SeenSlotInfo = true;
		ShowSlotInfo = true;
		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}
}

void UPlayerTutorialComponent::HasUsedSlot()
{
	if (ShowSlotInfo)
	{
		ShowSlotInfo = false;
		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}
}

void UPlayerTutorialComponent::InventoryPickUp()
{
	if (ShowInventoryPickup)
	{
		HasSeenInventoryPickup = true;
		ShowInventoryPickup = false;
		if (!HasSeenInventoryDrop) ShowInventoryDrop = true;
		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}
}

void UPlayerTutorialComponent::InventoryDrop()
{
	if (ShowInventoryDrop)
	{
		ShowInventoryDrop = false;
		HasSeenInventoryDrop = true;
		GetOwner<APlayerCharacter>()->GetHUD()->UpdateTutorialInfo();
	}
}

