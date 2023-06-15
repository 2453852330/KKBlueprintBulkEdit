// Fill out your copyright notice in the Description page of Project Settings.


#include "KKBlueprintBulkEditLib.h"
#include "Editor.h"
#include "Engine/Selection.h"
#include "Engine/TimelineTemplate.h"
#include "Kismet2/BlueprintEditorUtils.h"

void UKKBlueprintBulkEditLib::KK_GetBlueprintVariableList(
	FKKBlueprintWrapper & BPWrapper,TArray<FKKBPVariableInfo> & VarInfos
	)
{
	// 获取到编辑器选中的 Object
	USelection * Selections = GEditor->GetSelectedObjects();
	if (Selections->Num() <= 0 )
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Get Select Objects Failed, Num <= 0"));
		}
		UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Get Select Objects Failed, Num <= 0"),__FUNCTIONW__,__LINE__);
		return;
	}
	// 转换成 UBlueprint
	UBlueprint * BpObj = Cast<UBlueprint>(Selections->GetSelectedObject(0));
	if (!BpObj)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Cast Selected Object To UBlurprint Failed"));
		}
		UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Cast Selected Object To UBlurprint Failed"),__FUNCTIONW__,__LINE__);
		return;
	}
	// cache obj
	BPWrapper = FKKBlueprintWrapper(BpObj);
	
	for (FBPVariableDescription it : BpObj->NewVariables)
	{
		VarInfos.Add(FKKBPVariableInfo(
			it.VarName,
			it.FriendlyName,
			it.VarType.PinCategory,
			it.Category
		));
	}
}

void UKKBlueprintBulkEditLib::KK_SetBlueprintVariableCategory(UBlueprint* InBlueprint, FName VarName, FText NewCategory)
{
	if (InBlueprint)
	{
		FBlueprintEditorUtils::SetBlueprintVariableCategory(InBlueprint,VarName,nullptr,NewCategory);
	}
}

TArray<int32> UKKBlueprintBulkEditLib::KK_GetSelectedIndex(int32 Start, int32 End)
{
	TArray<int32> List;
	if (Start == End)
	{
		List.Add(Start);
	}
	else if( Start > End)
	{
		int32 Tmp = Start;
		while (Tmp >= End)
		{
			List.Add(Tmp--);
		}
	}
	else
	{
		int32 Tmp = Start;
		while (Tmp <= End)
		{
			List.Add(Tmp++);
		}
	}
	return List;
}

void UKKBlueprintBulkEditLib::KK_GetBlueprintFunctionList(FKKBlueprintWrapper & BPWrapper,TArray<FKKFuncEdGraphWrapper>& FuncList)
{
	// 获取到编辑器选中的 Object
	USelection * Selections = GEditor->GetSelectedObjects();
	if (Selections->Num() <= 0 )
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Get Select Objects Failed, Num <= 0"));
		}
		UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Get Select Objects Failed, Num <= 0"),__FUNCTIONW__,__LINE__);
		return;
	}
	// 转换成 UBlueprint
	UBlueprint * BpObj = Cast<UBlueprint>(Selections->GetSelectedObject(0));
	
	if (!BpObj)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Cast Selected Object To UBlurprint Failed"));
		}
		UE_LOG(LogTemp,Warning,TEXT("[%s::%d]:Cast Selected Object To UBlurprint Failed"),__FUNCTIONW__,__LINE__);
		return;
	}

	BPWrapper = FKKBlueprintWrapper(BpObj);
	/** NOTE: the event dont have Category */
	// for (UEdGraph* EventGraph : BpObj->EventGraphs)
	// {
	// 	FuncList.Add(FKKFuncEdGraphWrapper(EventGraph));
	// } 
	for (UEdGraph* FunctionGraph : BpObj->FunctionGraphs)
	{
		FuncList.Add(FKKFuncEdGraphWrapper(FunctionGraph));
	} 
	for (UEdGraph* MacroGraph : BpObj->MacroGraphs)
	{
		FuncList.Add(FKKFuncEdGraphWrapper(MacroGraph));
	}
}


void UKKBlueprintBulkEditLib::KK_SetBlueprintFunctionCategory(const FKKFuncEdGraphWrapper & Wrapper, FText NewCategory)
{
	if (Wrapper.Graph)
	{
		FBlueprintEditorUtils::SetBlueprintFunctionOrMacroCategory(Wrapper.Graph,NewCategory);
	}
}

void UKKBlueprintBulkEditLib::KK_GetInfoFromGraphWrapper(const FKKBlueprintWrapper & BPWrapper,const FKKFuncEdGraphWrapper& Wrapper,FKKGraphInfos & Infos)
{
	if (UEdGraph * Graph = Wrapper.Graph)
	{
		Infos.Name = Graph->GetName();
		if (BPWrapper.BPObj)
		{
			// UFunction Cant Find Macro
			UFunction* Function = nullptr;
			for (TFieldIterator<UFunction> FunctionIt(BPWrapper.BPObj->SkeletonGeneratedClass, EFieldIteratorFlags::IncludeSuper); FunctionIt; ++FunctionIt)
			{
				if (FunctionIt->GetName() == Graph->GetName())
				{
					Function = *FunctionIt;
					break;
				}
			}
			if (Function)
			{
				Infos.Category = Function->GetMetaData(FBlueprintMetadata::MD_FunctionCategory);
				// default is empty
				if (Infos.Category.IsEmpty())
				{
					Infos.Category = TEXT("Default");
				}
			}
			// its a Macro
			else
			{
				FKismetUserDeclaredFunctionMetadata* MetaData = FBlueprintEditorUtils::GetGraphFunctionMetaData(Graph);
				Infos.Category = MetaData?MetaData->Category.ToString():TEXT("Cant Get For Macro");
				if (Infos.Category.IsEmpty())
				{
					Infos.Category = TEXT("Default");
				}
			}
		}
	}
}

