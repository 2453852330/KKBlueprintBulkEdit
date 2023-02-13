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
	static FString KK_GetBlueprintVariableList(TArray<FName> & VarList ,TArray<FText> & CategoryList, FKKBpObjRef & Obj , bool bEnableSuper,bool bEnablePrivate);

	UFUNCTION(BlueprintCallable,Category="KKBPBuldEdit")
	static void KK_SetBlurptinyVariableCategory(const FKKBpObjRef & obj ,const FText & NewText,FName VarName,bool bRecompile);
};
