// Fill out your copyright notice in the Description page of Project Settings.


#include "KKBlueprintBulkEditLib.h"

#include "Editor.h"
#include "KKBPBulkEdit.h"
#include "ObjectEditorUtils.h"
#include "Engine/Selection.h"
#include "Engine/TimelineTemplate.h"
#include "Kismet2/BlueprintEditorUtils.h"

FString UKKBlueprintBulkEditLib::KK_GetBlueprintVariableList(TArray<FName>& VarList,TArray<FText> & CategoryList , FKKBpObjRef& Obj,bool bEnableSuper,bool bEnablePrivate)
{
	// 获取到编辑器选中的 Object
	USelection * Selections = GEditor->GetSelectedObjects();
	if (!Selections || Selections->Num() <=0)
	{
		return TEXT("No Select Object");
	}
	// 转换成 UBlueprint
	UBlueprint * BpObj = Cast<UBlueprint>(Selections->GetSelectedObject(0));
	if (!BpObj || !BpObj->SkeletonGeneratedClass)
	{
		return TEXT("Get Blueprint Info Failed");
	}
	// create set to save list
	TSet<FName> tmp_var_list;
	// 获取到 UBlueprint 的结构类
	// 通过迭代器反射遍历 FProperty : 迭代器参数可选: 是否获取父类 ? 
	for (TFieldIterator<FProperty> PropertyIt(BpObj->SkeletonGeneratedClass,bEnableSuper?EFieldIteratorFlags::IncludeSuper:EFieldIteratorFlags::ExcludeSuper);
		PropertyIt; ++PropertyIt)
	{
		FProperty* Property = *PropertyIt;
		// 如果属性没有 flag 是函数参数 && (允许私有 || 是否是蓝图可见变量);  
		if ((!Property->HasAnyPropertyFlags(CPF_Parm) && (bEnablePrivate || Property->HasAllPropertyFlags(CPF_BlueprintVisible))))
		{
			tmp_var_list.Add(Property->GetFName());
		}
	}

	if (bEnablePrivate)
	{
		// Include SCS node variable names, timelines, and other member variables that may be pending compilation. Consider them to be "private" as they're not technically accessible for editing just yet.
		TArray<UBlueprint*> ParentBPStack;
		// 获取所有的父类 UBlueprint ;
		UBlueprint::GetBlueprintHierarchyFromClass(BpObj->SkeletonGeneratedClass, ParentBPStack);
		// the index 0 is self
		for (int32 StackIndex = ParentBPStack.Num() - 1; StackIndex >= 0; --StackIndex)
		{
			UBlueprint* ParentBP = ParentBPStack[StackIndex];
			check(ParentBP != nullptr);
			
			// 不知道有啥用 
			// FBlueprintEditorUtils::GetSCSVariableNameList(ParentBP, tmp_var_list);
			
			for (int32 VariableIndex = 0; VariableIndex < ParentBP->NewVariables.Num(); ++VariableIndex)
			{
				tmp_var_list.Add(ParentBP->NewVariables[VariableIndex].VarName);
			}
			// timeline变量
			for (UTimelineTemplate* Timeline : ParentBP->Timelines)
			{
				if (Timeline)
				{
					tmp_var_list.Add(Timeline->GetFName());
				}
			}
		}
	}
	UE_LOG(LogTemp,Warning,TEXT("find var name list finish"));
	// 遍历找到的变量名列表,同时获取原来的Category;
	for (FName it : tmp_var_list)
	{
		VarList.Add(it);

		// 尝试获取 Category
		FText CategoryName;
		FProperty * TargetProperty = FindFProperty<FProperty>(BpObj->SkeletonGeneratedClass,it);
		if (TargetProperty != nullptr)
		{
			CategoryName = FObjectEditorUtils::GetCategoryText(TargetProperty);
			CategoryList.Add(CategoryName);
		}
		else
		{
			// 没有找到就填写NULL,防止数据不匹配
			CategoryList.Add(FText::FromString("NULL"));
		}
	}
	// cache obj
	Obj.obj = BpObj;
	return TEXT("Success");
}

void UKKBlueprintBulkEditLib::KK_SetBlurptinyVariableCategory(const FKKBpObjRef& obj, const FText& NewText,
	FName VarName, bool bRecompile)
{
	FText CategoryName = FText::TrimPrecedingAndTrailing(NewText);
	FBlueprintEditorUtils::SetBlueprintVariableCategory(obj.obj,VarName,nullptr,NewText,bRecompile);
}
