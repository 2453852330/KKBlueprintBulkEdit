// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KKBlurprintBulkEditType.h"
#include "KKBlueprintBulkEditLib.generated.h"

/**
 * 
 */
UCLASS()
class KKBLUEPRINTBULKEDIT_API UKKBlueprintBulkEditLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** Read The Blueprint Created Variable infos */
	UFUNCTION(BlueprintCallable,Category="KKBPBulkEdit")
	static void KK_GetBlueprintVariableList(FKKBlueprintWrapper & BPWrapper,TArray<FKKBPVariableInfo> & VarInfos);

	/** Update the blueprint Variable's Category  */
	UFUNCTION(BlueprintCallable,Category="KKBPBulkEdit")
	static void KK_SetBlueprintVariableCategory(UBlueprint * InBlueprint,FName VarName,FText NewCategory);

	/** helper to create index array of selected item  */
	UFUNCTION(BlueprintCallable,Category="KKBPBulkEdit")
	static TArray<int32> KK_GetSelectedIndex(int32 Start,int32 End);

	/** Get Function EdGraph List */
	UFUNCTION(BlueprintCallable,Category="KKBPBulkEdit")
	static void KK_GetBlueprintFunctionList(FKKBlueprintWrapper & BPWrapper,TArray<FKKFuncEdGraphWrapper> & FuncList);

	/** Set the function's Category */
	UFUNCTION(BlueprintCallable,Category="KKBPBulkEdit")
	static void KK_SetBlueprintFunctionCategory(const FKKFuncEdGraphWrapper & Wrapper,FText NewCategory);

	/** helper get info from EdGraph */
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="KKBPBulkEdit")
	static void KK_GetInfoFromGraphWrapper(const FKKBlueprintWrapper & BPWrapper,const FKKFuncEdGraphWrapper & Wrapper,FKKGraphInfos & Infos);
};
