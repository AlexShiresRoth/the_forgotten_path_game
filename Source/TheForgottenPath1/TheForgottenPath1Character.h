// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TheForgottenPath1Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class UHero_Character_Widget;
class UMenu_Widget;
class UInventory_Widget;
class AInventoryItem;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

USTRUCT(BlueprintType)
struct FPlayerCharacterInventoryState
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory State")
	TArray<AInventoryItem *> InventoryItemsList;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	bool bHasBeenInteractedWith = false;

	UPROPERTY(BlueprintReadWrite, Category = "State")
	int32 TimesAccessed = 0;

	FPlayerCharacterInventoryState()
		: bHasBeenInteractedWith(false), TimesAccessed(0)
	{
	}
};

UCLASS(config = Game)
class ATheForgottenPath1Character : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent *CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent *FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext *DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *LookAction;

	/** Main Menu Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *MainMenuAction;

	/** Inventory Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *InventoryAction;

public:
	ATheForgottenPath1Character();

	float CharacterCurrentHealth = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UHero_Character_Widget> CharacterWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UHero_Character_Widget *CharacterWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UMenu_Widget> MainMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UMenu_Widget *MainMenuWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UInventory_Widget> InventoryWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UInventory_Widget *InventoryWidgetInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Data")
	bool bIsDead = false;

	// set widget to viewport
	UFUNCTION()
	void ShowCharacterWidget();

	UFUNCTION()
	void ToggleMainMenuWidget();

	UFUNCTION()
	void ToggleInventoryWidget();

	UFUNCTION(BlueprintCallable, Category = "Character Data")
	float GetCharacterCurrentHealth();

	UFUNCTION()
	float SetCharacterCurrentHealth(float NewHealth);

	UFUNCTION()
	void AddItemToInventory(AInventoryItem *Item);

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetMouseCursorVisible(bool bVisible);

	void EnterRagdoll();

protected:
	/** Called for movement input */
	void Move(const FInputActionValue &Value);

	/** Called for looking input */
	void Look(const FInputActionValue &Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent *GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent *GetFollowCamera() const { return FollowCamera; }

private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory State")
	FPlayerCharacterInventoryState InventoryState;
};