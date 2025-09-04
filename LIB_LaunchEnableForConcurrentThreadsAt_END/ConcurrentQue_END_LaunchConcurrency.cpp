#include "pch.h"

#include <cstddef>

class Avril_FSD::ConcurrentQue_END_Global* ptr_Global = NULL;
class Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control* ptr_LaunchConcurrency_Control = NULL;

Avril_FSD::ConcurrentQue_END_LaunchConcurrency::ConcurrentQue_END_LaunchConcurrency()
{
    Create_ConcurrentQue_END_Global();
}

Avril_FSD::ConcurrentQue_END_LaunchConcurrency::~ConcurrentQue_END_LaunchConcurrency()
{
    delete ptr_LaunchConcurrency_Control;
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency::Initialise_Control()
{
    Create_Control_Of_LaunchConcurrency();
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency::Thread_Start(class Avril_FSD::ConcurrentQue_END_Framework* obj, unsigned char concurrent_CoreId)
{
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->LaunchEnable_Request(obj, concurrent_CoreId);
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->LaunchQue_Update(obj, obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_number_Implemented_Cores());
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->LaunchEnable_SortQue(obj, obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_number_Implemented_Cores());
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->LaunchEnable_Activate(obj);
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->LaunchQue_Update(obj, obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_number_Implemented_Cores());
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->LaunchEnable_SortQue(obj, obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_number_Implemented_Cores());
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_flag_praisingLaunch(false);
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency::Thread_End(class Avril_FSD::ConcurrentQue_END_Framework* obj, unsigned char concurrent_CoreId)
{
    while (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_flag_praisingLaunch() == true)
    {

    }
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_flag_praisingLaunch(true);
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_concurrentCycle_Try_CoreId_Index(obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_new_concurrentCycle_Try_CoreId_Index());
    if (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_concurrentCycle_Try_CoreId_Index() == concurrent_CoreId)
    {
        obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_state_ConcurrentCore(concurrent_CoreId, obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_flag_core_IDLE());
    }
    else
    {
        obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_new_concurrentCycle_Try_CoreId_Index(obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_concurrentCycle_Try_CoreId_Index() + 1);

        if (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_new_concurrentCycle_Try_CoreId_Index() == 3)//NUMBER OF CONCURNT CORES
        {
            obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_new_concurrentCycle_Try_CoreId_Index(0);
        }
        obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_flag_praisingLaunch(false);
        obj->Get_ConcurrentQue()->Thread_End(obj, concurrent_CoreId);
    }
}
void Avril_FSD::ConcurrentQue_END_LaunchConcurrency::Create_ConcurrentQue_END_Global()
{
    Set_LaunchConcurrency_Global(new class Avril_FSD::ConcurrentQue_END_Global());
    while (Get_class_LaunchConcurrency_Global() == NULL) {}
}
void Avril_FSD::ConcurrentQue_END_LaunchConcurrency::Create_Control_Of_LaunchConcurrency()
{
    Set_Control_Of_LaunchConcurrency(new class Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control(Get_class_LaunchConcurrency_Global(), Get_class_LaunchConcurrency_Global()->Get_number_Implemented_Cores()));
    while (Get_class_Control_Of_LaunchConcurrency() == NULL) { /* wait untill created */ }
}
Avril_FSD::ConcurrentQue_END_Global* Avril_FSD::ConcurrentQue_END_LaunchConcurrency::Get_class_LaunchConcurrency_Global()
{
    return ptr_Global;
}
Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control* Avril_FSD::ConcurrentQue_END_LaunchConcurrency::Get_class_Control_Of_LaunchConcurrency()
{
    return ptr_LaunchConcurrency_Control;
}
Avril_FSD::ConcurrentQue_END_Global* Avril_FSD::ConcurrentQue_END_LaunchConcurrency::Get_LaunchConcurrency_Global()
{
    return ptr_Global;
}
Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control* Avril_FSD::ConcurrentQue_END_LaunchConcurrency::Get_Control_Of_LaunchConcurrency()
{
    return ptr_LaunchConcurrency_Control;
}
void Avril_FSD::ConcurrentQue_END_LaunchConcurrency::Set_LaunchConcurrency_Global(ConcurrentQue_END_Global* global)
{
    ptr_Global = global;
}
void Avril_FSD::ConcurrentQue_END_LaunchConcurrency::Set_Control_Of_LaunchConcurrency(ConcurrentQue_END_LaunchConcurrency_Control* control)
{
    ptr_LaunchConcurrency_Control = control;
}