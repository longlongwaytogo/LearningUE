#include "SimpleAsyncTasks.h"
#include "SimpleRunnable.h"
// �����棬FSimpleAsyncTasks::GetStatId ����cpp��Ҳ��inline ����ֻ�ܷ���SimpleActor���У���������һ���࣬ȴ���ܱ���ͨ����
// 
//FSimpleAsyncTasks::FSimpleAsyncTasks(int32 Input1, int32 Input2):MyInput1(Input1),
//MyInput2(Input2)
//{
//	 
//}
//
//FORCEINLINE TStatId FSimpleAsyncTasks::GetStatId() const
//{
//	RETURN_QUICK_DECLARE_CYCLE_STAT(FSimpleAsyncTasks, STATGROUP_ThreadPoolAsyncTasks);
//}
// 
//
//void FSimpleAsyncTasks::DoWork()
//{
//	for (int i = 1; i < 6; i++)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("SimpleAsyncTasks Dowork %d"), i);
//		FPlatformProcess::Sleep(0.2);
//	}
//
//}
