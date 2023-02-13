// Fill out your copyright notice in the Description page of Project Settings.


#include "KKBlueprintBulkEditLib.h"

#include "Editor.h"
#include "KKBPBulkEdit.h"
#include "Engine/Selection.h"
#include "Kismet2/BlueprintEditorUtils.h"


void UKKBlueprintBulkEditLib::KK_GetBlueprintInfo(TArray<FString> & VarList , FKKBpObjRef & obj)
{
	// Blueprint'/KKBlueprintBulkEdit/BP_TestBP.BP_TestBP'
	// 寻找当前选中的对象
	USelection * Selections = GEditor->GetSelectedObjects();
	UE_LOG(LogTemp,Warning,TEXT("find %d obj"),Selections->Num());
	for (int i = 0 ; i < Selections->Num() ; ++i)
	{
		UE_LOG(LogTemp,Warning,TEXT("selected obj's name : %s"),*Selections->GetSelectedObject(i)->GetName());
	}
	TArray<UObject*> SelectObjs;
	Selections->GetSelectedObjects(SelectObjs);
	
	// 如果是BP
	if (Selections->Num() <= 0)
	{
		UE_LOG(LogTemp,Warning,TEXT("no selected obj"));
		return;
	}

	// get class name is : Blueprint
	UObject * tmp_obj = SelectObjs[0];
	UBlueprint * tmp_bp = Cast<UBlueprint>(tmp_obj);
	if (!tmp_bp)
	{
		UE_LOG(LogTemp,Warning,TEXT("cast to UBlueprint failed"));
		return;
	}
	UE_LOG(LogTemp,Warning,TEXT("cast to UBlueprint success"));
	TSet<FName> var_list;
	FBlueprintEditorUtils::GetClassVariableList(tmp_bp,var_list);
	UE_LOG(LogTemp,Warning,TEXT("find %d var"),var_list.Num());
	for (FName it : var_list)
	{
		// UE_LOG(LogTemp,Warning,TEXT("var name = %s"),*it.ToString());
		VarList.Add(it.ToString());
	}
	obj.obj = tmp_bp;
}

void UKKBlueprintBulkEditLib::KK_SetCategory(const FKKBpObjRef & obj, const FText& NewText, FName VarName)
{
	FText CategoryName = FText::TrimPrecedingAndTrailing(NewText);
	UStruct * VarStruct = nullptr;
	FBlueprintEditorUtils::GetBlueprintVariableCategory(obj.obj,VarName,VarStruct);
	FBlueprintEditorUtils::SetBlueprintVariableCategory(obj.obj,VarName,VarStruct,NewText,false);
}
