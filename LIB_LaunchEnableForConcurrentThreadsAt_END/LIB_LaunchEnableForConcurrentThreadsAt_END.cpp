// LIB_ConcurrentQue_END.cpp : Defines the exported functions for the DLL.
#include "pch.h"
#include "framework.h"
#include "LIB_LaunchEnableForConcurrentThreadsAt_END.h"

class Avril_FSD::ConcurrentQue_END_Framework* ptr_ConcurrentQue_END_Framework = NULL;

Avril_FSD::ConcurrentQue_END_Library::ConcurrentQue_END_Library()
{

}

// This is an example of an exported function.
void* Avril_FSD::ConcurrentQue_END_Library::Initialise_ConcurrentQue()
{
    Set_ConcurrentQue_END_Framework(new class Avril_FSD::ConcurrentQue_END_Framework());
    while (Get_ConcurrentQue_END_Framework() == NULL) {}
    return (void*)Get_ConcurrentQue_END_Framework();
}

void Avril_FSD::ConcurrentQue_END_Library::Request_Wait_Launch(Avril_FSD::ConcurrentQue_END_Framework* obj, unsigned char concurrent_CoreId)
{
    obj->Get_ConcurrentQue()->Thread_Start(obj, concurrent_CoreId);
}

void Avril_FSD::ConcurrentQue_END_Library::Thread_End(Avril_FSD::ConcurrentQue_END_Framework* obj, unsigned char concurrent_CoreId)
{
    obj->Get_ConcurrentQue()->Thread_End(obj, concurrent_CoreId);
}

__int8 Avril_FSD::ConcurrentQue_END_Library::Get_coreId_To_Launch(Avril_FSD::ConcurrentQue_END_Framework* obj)
{
    return obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_que_CoreToLaunch(0);
}

bool Avril_FSD::ConcurrentQue_END_Library::Get_Flag_Active(Avril_FSD::ConcurrentQue_END_Framework* obj)
{
    return obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_flag_core_ACTIVE();
}

bool Avril_FSD::ConcurrentQue_END_Library::Get_Flag_ConcurrentCoreState(Avril_FSD::ConcurrentQue_END_Framework* obj, unsigned char concurrent_CoreId)
{
    return obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_state_ConcurrentCore(concurrent_CoreId);
}

bool Avril_FSD::ConcurrentQue_END_Library::Get_Flag_Idle(Avril_FSD::ConcurrentQue_END_Framework* obj)
{
    return obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_flag_core_IDLE();
}

bool Avril_FSD::ConcurrentQue_END_Library::Get_State_LaunchBit(Avril_FSD::ConcurrentQue_END_Framework* obj)
{
    return obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_state_ConcurrentCore(0);
}

void Avril_FSD::ConcurrentQue_END_Library::Set_state_ConcurrentCore(Avril_FSD::ConcurrentQue_END_Framework* obj, unsigned char concurrent_CoreId, bool value)
{
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_state_ConcurrentCore(concurrent_CoreId, value);
}

Avril_FSD::ConcurrentQue_END_Framework* Avril_FSD::ConcurrentQue_END_Library::Get_ConcurrentQue_END_Framework()
{
    return ptr_ConcurrentQue_END_Framework;
}

void Avril_FSD::ConcurrentQue_END_Library::Set_ConcurrentQue_END_Framework(class Avril_FSD::ConcurrentQue_END_Framework* framework)
{
    ptr_ConcurrentQue_END_Framework = framework;
}
