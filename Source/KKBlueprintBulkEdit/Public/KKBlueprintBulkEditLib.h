// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KKBPBulkEdit.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KKBlueprintBulkEditLib.generated.h"


/**
 * 
 */
UCLASS()
class KKBLUEPRINTBULKEDIT_API UKKBlueprintBulkEditLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,Category="KKBPBulkEdit")
	static void KK_GetBlueprintInfo(TArray<FString> & VarList , FKKBpObjRef & Obj);

	UFUNCTION(BlueprintCallable,Category="KKBPBuldEdit")
	static void KK_SetCategory(const FKKBpObjRef & obj ,const FText & NewText,FName VarName);
	
};
