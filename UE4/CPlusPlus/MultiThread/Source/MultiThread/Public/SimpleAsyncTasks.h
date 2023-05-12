#pragma once
#include "CoreMinimal.h"
 
//
//class FSimpleAsyncTasks : public FNonAbandonableTask
//{
//	friend class FAutoDeleteAsyncTask<FSimpleAsyncTasks>;
//public:
//	FSimpleAsyncTasks(int32 Input1, int32 Input2);
//
//protected:
//	int32 MyInput1;
//	int32 MyInput2;
//
//	void DoWork();
//	FORCEINLINE TStatId GetStatId() const;
//	/*FORCEINLINE TStatId GetStatId() const
//	{
//		RETURN_QUICK_DECLARE_CYCLE_STAT(FSimpleAsyncTasks, STATGROUP_ThreadPoolAsyncTasks);
//	}*/
//};