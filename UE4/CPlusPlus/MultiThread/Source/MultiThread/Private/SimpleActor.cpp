// Fill out your copyright notice in the Description page of Project Settings.
// https://github.com/tiax615/UE4_MultiThread

#include "SimpleActor.h"
#include "SimpleRunnable.h"
#include "TimerManager.h"
#include "SimpleAsyncTasks.h"

// Sets default values
ASimpleActor::ASimpleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimpleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimpleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASimpleActor::RunSimpleRunnable()
{
	FSimpleRunnable::JoyInit();
}

void ASimpleActor::StopSimpleRunnable()
{
	FSimpleRunnable::Shutdown();
}


void test(int i)
{
	printf("%d\n", i);
	
}

 

namespace SimpleTaskGraph
{
	FGraphEventArray SimpleTask_CompletionEvents; // 保存任务的数组
	static	int Number = 0; // 打印的数字 ，从0 开始
	
	
	
	 bool  TasksAreComplete()
	{
		for (int32 Index = 0; Index < SimpleTask_CompletionEvents.Num(); Index++)
		{
			if (!SimpleTask_CompletionEvents[Index]->IsComplete())
			{
				return false;
			}
		}
		return true;
	}


	static int GetNextInt()
	{
		FPlatformProcess::Sleep(0.1);
		Number++;
		UE_LOG(LogTemp, Warning, TEXT("show SimpleTask %d"), Number);
		return Number;

	}

	// Each task Thread
	class SimpleTask
	{
	public:
		SimpleTask() {}

		// get name 
		static const TCHAR* GetTaskName()
		{
			return TEXT("SimpleTask");
		}

		FORCEINLINE static TStatId GetStatId()
		{
			RETURN_QUICK_DECLARE_CYCLE_STAT(SimpleTask, STATGROUP_TaskGraphTasks);
		}
		static ESubsequentsMode::Type GetSubsequentsMode()
		{
				return ESubsequentsMode::TrackSubsequents;
		}
		static ENamedThreads::Type GetDesiredThread()
		{
			return ENamedThreads::AnyThread;
		}


		// Main function: DO Task!
		void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
		{
			GetNextInt();
		}
	};
	// 使用命名空间SimpleTaskGraph的这个方法，开启任务图
	void GetInts(const uint32 TotalToGet)
	{
		Number = 0;
		while(SimpleTask_CompletionEvents.Num()>0)
		{
			SimpleTask_CompletionEvents.RemoveAt(0);
		}
		for (uint32 i = 0; i < TotalToGet; i++)
		{
			// 第一个变量等待其中的任务完成，然后再进行下一个任务
			// 第一个变量官方Wiki是NULL，这样可以不按照顺序执行
			SimpleTask_CompletionEvents.Add(TGraphTask<SimpleTask>::CreateTask(
				&SimpleTask_CompletionEvents, ENamedThreads::GameThread).ConstructAndDispatchWhenReady());
		}
	}
}


void ASimpleActor::StartTask(int TotalToGet)
{
	SimpleTaskGraph::GetInts(TotalToGet);
	GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ASimpleActor::CheckAllTasksDone, 1, true);
}

void ASimpleActor::CheckAllTasksDone()
{
	if (SimpleTaskGraph::TasksAreComplete())
	{
		GetWorldTimerManager().ClearTimer(MyTimerHandle);
		UE_LOG(LogTemp, Warning, TEXT("TaskGraph Done!"));
	}
}

void ASimpleActor::StartAsyncTask()
{
	// Instantiate a copy of the actual task, and queue the task for execution with StartBackgroundTask()
	(new FAutoDeleteAsyncTask<FSimpleAsyncTasks>(6, 6))->StartBackgroundTask();
}


FSimpleAsyncTasks::FSimpleAsyncTasks(int32 Input1, int32 Input2) :MyInput1(Input1),
MyInput2(Input2)
{

}

FORCEINLINE TStatId FSimpleAsyncTasks::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(FSimpleAsyncTasks, STATGROUP_ThreadPoolAsyncTasks);
}


void FSimpleAsyncTasks::DoWork()
{
	for (int i = 1; i < 6; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("SimpleAsyncTasks Dowork %d"), i);
		FPlatformProcess::Sleep(0.2);
	}

}
