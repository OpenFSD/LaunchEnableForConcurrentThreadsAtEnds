#include "pch.h"

#include <cstddef>
#include <vector>

unsigned char _concurrentCycle_Try_CoreId_Index = NULL;
int _count_LaunchActive_For[3] = { NULL, NULL, NULL };//NUMBER OF CONCURNT CORES
int _count_LaunchIdle_For[3] = { NULL, NULL, NULL };//NUMBER OF CONCURNT CORES
bool _flag_praisingLaunch = NULL;
std::vector<unsigned char>* _stack_PriseEventId;
bool _state_ConcurrentCore[3] = { NULL, NULL, NULL };//NUMBER OF CONCURRENT CORES
unsigned char _new_concurrentCycle_Try_CoreId_Index = NULL;
unsigned char _que_CoreToLaunch[3] = { NULL, NULL, NULL };//NUMBER OF CONCURRENT CORES

Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::ConcurrentQue_END_LaunchConcurrency_Control(Avril_FSD::ConcurrentQue_END_Global* global, unsigned char number_Implemented_Cores)
{
    Set_concurrentCycle_Try_CoreId_Index(0);
    for (__int8 index = 0; index < global->Get_number_Implemented_Cores() - 1; index++)//NUMBER OF CONCURRENT CORES
    {
        Set_count_LaunchActive_For(0, index);
    }
    for (__int8 index = 0; index < global->Get_number_Implemented_Cores() - 1; index++)//NUMBER OF CONCURRENT CORES
    {
        Set_count_LaunchIdle_For(0, index);
    }
    Set_flag_praisingLaunch(false);
    Set_stack_PriseEventId(new std::vector<unsigned char>);
    for (__int8 index = 0; index < global->Get_number_Implemented_Cores() - 1; index++)//NUMBER OF CONCURRENT CORES
    {
        Set_state_ConcurrentCore(global->Get_flag_core_IDLE(), index);
    }
    Set_new_concurrentCycle_Try_CoreId_Index(1);
    for (__int8 index = 0; index < global->Get_number_Implemented_Cores() - 1; index++)//NUMBER OF CONCURRENT CORES
    {
        Set_que_CoreToLaunch(index, index);
    }
}

Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::~ConcurrentQue_END_LaunchConcurrency_Control()
{

}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::LaunchEnable_Activate(Avril_FSD::ConcurrentQue_END_Framework* obj)
{
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_state_ConcurrentCore(obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_flag_core_ACTIVE(), obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_que_CoreToLaunch(0));
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::LaunchEnable_Request(Avril_FSD::ConcurrentQue_END_Framework* obj, unsigned char concurrent_CoreId)
{
    while (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_state_ConcurrentCore(Get_flag_CoreId_Of_CoreToLaunch()) != obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_flag_core_IDLE())
    {

    }
    while (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_flag_praisingLaunch() == true)
    {
        obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->DynamicStagger(obj, concurrent_CoreId);
    }
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_flag_praisingLaunch(true);
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_concurrentCycle_Try_CoreId_Index(Get_new_concurrentCycle_Try_CoreId_Index());
    if (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_concurrentCycle_Try_CoreId_Index() == concurrent_CoreId)
    {
        //exit
    }
    else
    {
        obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_new_concurrentCycle_Try_CoreId_Index(Get_concurrentCycle_Try_CoreId_Index() + 1);
        if (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_concurrentCycle_Try_CoreId_Index() == 3)//NUMBER OF CONCURRENT CORES
        {
            obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_new_concurrentCycle_Try_CoreId_Index(0);
        }
        obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_flag_praisingLaunch(false);
        obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->LaunchEnable_Request(obj, concurrent_CoreId);
    }
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::LaunchEnable_SortQue(Avril_FSD::ConcurrentQue_END_Framework* obj, unsigned char number_Implemented_Cores)
{
    for (unsigned char index_A = 0; index_A < number_Implemented_Cores - 2; index_A++)
    {
        for (unsigned char index_B = index_A + 1; index_B < number_Implemented_Cores - 1; index_B++)
        {
            if (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_state_ConcurrentCore(Get_que_CoreToLaunch(index_A)) == obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_flag_core_ACTIVE())
            {
                if (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_state_ConcurrentCore(Get_que_CoreToLaunch(index_B)) == obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_flag_core_IDLE())
                {
                    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->LaunchEnable_ShiftQueValues(obj, index_A, index_B);
                }
                else if (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_state_ConcurrentCore(obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_que_CoreToLaunch(index_B)) == obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_flag_core_ACTIVE())
                {
                    if (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_count_LaunchActive_For(index_A) > obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_count_LaunchActive_For(index_B))
                    {
                        obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->LaunchEnable_ShiftQueValues(obj, index_A, index_B);
                    }
                }
            }
            else if (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_state_ConcurrentCore(obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_que_CoreToLaunch(index_A)) == obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_flag_core_IDLE())

                if (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_state_ConcurrentCore(obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_que_CoreToLaunch(index_B)) == obj->Get_ConcurrentQue()->Get_LaunchConcurrency_Global()->Get_flag_core_IDLE())
                {
                    if (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_count_LaunchIdle_For(index_A) < obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_count_LaunchIdle_For(index_B))
                    {
                        obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->LaunchEnable_ShiftQueValues(obj, index_A, index_B);
                    }
                }
        }
    }
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::LaunchQue_Update(Avril_FSD::ConcurrentQue_END_Framework* obj, unsigned char number_Implemented_Cores)
{
    for (unsigned char index = 0; index < number_Implemented_Cores; index++)
    {
        switch (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_state_ConcurrentCore(index))
        {
        case false:
        {
            obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_count_LaunchActive_For(index, 0);
            obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_count_LaunchIdle_For(index, obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_count_LaunchIdle_For(index) + 1);
            break;
        }
        case true:
        {
            obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_count_LaunchActive_For(index, obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_count_LaunchActive_For(index) + 1);
            obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_count_LaunchIdle_For(index, 0);
            break;
        }
        }
    }
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::DynamicStagger(Avril_FSD::ConcurrentQue_END_Framework* obj, unsigned char concurrent_CoreId)
{
    if (obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_concurrentCycle_Try_CoreId_Index() == concurrent_CoreId)
    {
        //exit early
    }
    else
    {
        int ptr_count = int(0);
        while (ptr_count < 20)//todo time till flag change
        {

            ptr_count = ptr_count + 1;
        }
    }
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::LaunchEnable_ShiftQueValues(Avril_FSD::ConcurrentQue_END_Framework* obj, unsigned char concurrent_CoreId_A, unsigned char concurrent_CoreId_B)
{
    int temp_Int;
    temp_Int = obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_count_LaunchActive_For(concurrent_CoreId_A);
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_count_LaunchActive_For(concurrent_CoreId_A, obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_count_LaunchActive_For(concurrent_CoreId_B));
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_count_LaunchActive_For(concurrent_CoreId_B, temp_Int);

    temp_Int = obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_count_LaunchIdle_For(concurrent_CoreId_A);
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_count_LaunchIdle_For(concurrent_CoreId_A, obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_count_LaunchIdle_For(concurrent_CoreId_B));
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_count_LaunchIdle_For(concurrent_CoreId_B, temp_Int);

    unsigned char temp_UnnsignedChar;
    temp_UnnsignedChar = obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_que_CoreToLaunch(concurrent_CoreId_A);
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_que_CoreToLaunch(concurrent_CoreId_A, obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Get_que_CoreToLaunch(concurrent_CoreId_B));
    obj->Get_ConcurrentQue()->Get_Control_Of_LaunchConcurrency()->Set_que_CoreToLaunch(concurrent_CoreId_B, temp_UnnsignedChar);
}

unsigned char Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Get_concurrentCycle_Try_CoreId_Index()
{
    return _concurrentCycle_Try_CoreId_Index;
}

int Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Get_count_LaunchActive_For(unsigned char concurrent_CoreId)
{
    return _count_LaunchActive_For[concurrent_CoreId];
}

int Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Get_count_LaunchIdle_For(unsigned char concurrent_CoreId)
{
    return _count_LaunchIdle_For[concurrent_CoreId];
}

bool Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Get_flag_praisingLaunch()
{
    return _flag_praisingLaunch;
}

std::vector<unsigned char>* Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Get_stack_PriseEventId()
{
    return _stack_PriseEventId;
}

bool Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Get_state_ConcurrentCore(unsigned char concurrent_CoreId)
{
    return _state_ConcurrentCore[concurrent_CoreId];
}

unsigned char Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Get_new_concurrentCycle_Try_CoreId_Index()
{
    return _new_concurrentCycle_Try_CoreId_Index;
}

unsigned char Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Get_flag_CoreId_Of_CoreToLaunch()
{
    return _que_CoreToLaunch[0];
}

unsigned char Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Get_que_CoreToLaunch(unsigned char index)
{
    return _que_CoreToLaunch[index];
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Set_concurrentCycle_Try_CoreId_Index(unsigned char concurrentCycle_Try_CoreId_Index)
{
    _concurrentCycle_Try_CoreId_Index = concurrentCycle_Try_CoreId_Index;
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Set_count_LaunchActive_For(int count_LaunchActive_For, unsigned char concurrent_CoreId)
{
    _count_LaunchActive_For[concurrent_CoreId] = count_LaunchActive_For;
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Set_count_LaunchIdle_For(int count_LaunchIdle_For, unsigned char concurrent_CoreId)
{
    _que_CoreToLaunch[concurrent_CoreId] = count_LaunchIdle_For;
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Set_flag_praisingLaunch(bool flag_praisingLaunch)
{
    _flag_praisingLaunch = flag_praisingLaunch;
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Set_stack_PriseEventId(std::vector<unsigned char>* stack_PriseEventId)
{
    _stack_PriseEventId = stack_PriseEventId;
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Set_state_ConcurrentCore(bool state_ConcurrentCore, unsigned char concurrent_CoreId)
{
    _state_ConcurrentCore[concurrent_CoreId] = state_ConcurrentCore;
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Set_new_concurrentCycle_Try_CoreId_Index(unsigned char new_concurrentCycle_Try_CoreId_Index)
{
    _new_concurrentCycle_Try_CoreId_Index = new_concurrentCycle_Try_CoreId_Index;
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::Set_que_CoreToLaunch(unsigned char concurrent_CoreId, unsigned char value)
{
    _que_CoreToLaunch[concurrent_CoreId] = value;
}