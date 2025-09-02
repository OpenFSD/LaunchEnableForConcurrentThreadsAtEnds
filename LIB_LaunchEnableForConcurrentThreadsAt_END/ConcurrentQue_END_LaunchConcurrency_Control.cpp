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

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::LaunchEnable_Activate(class Avril_FSD::ConcurrentQue_END_Global* global)
{
    Set_state_ConcurrentCore(Get_flag_CoreId_Of_CoreToLaunch(), global->Get_flag_core_ACTIVE());
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::LaunchEnable_Request(unsigned char concurrent_CoreId, class Avril_FSD::ConcurrentQue_END_Global* global)
{
    while (Get_state_ConcurrentCore(Get_flag_CoreId_Of_CoreToLaunch()) != global->Get_flag_core_IDLE())
    {

    }
    while (Get_flag_praisingLaunch() == true)
    {
        DynamicStagger(concurrent_CoreId);
    }
    Set_flag_praisingLaunch(true);
    Set_concurrentCycle_Try_CoreId_Index(Get_new_concurrentCycle_Try_CoreId_Index());
    if (Get_concurrentCycle_Try_CoreId_Index() == concurrent_CoreId)
    {

    }
    else
    {
        Set_new_concurrentCycle_Try_CoreId_Index(Get_concurrentCycle_Try_CoreId_Index() + 1);
        if (Get_concurrentCycle_Try_CoreId_Index() == 3)//NUMBER OF CONCURRENT CORES
        {
            Set_new_concurrentCycle_Try_CoreId_Index(0);
        }
        Set_flag_praisingLaunch(false);
        LaunchEnable_Request(concurrent_CoreId, global);
    }
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::LaunchEnable_SortQue(class Avril_FSD::ConcurrentQue_END_Global* ptr_Global, unsigned char number_Implemented_Cores)
{
    for (unsigned char index_A = 0; index_A < number_Implemented_Cores - 2; index_A++)
    {
        for (unsigned char index_B = index_A + 1; index_B < number_Implemented_Cores - 1; index_B++)
        {
            if (Get_state_ConcurrentCore(Get_que_CoreToLaunch(index_A)) == ptr_Global->Get_flag_core_ACTIVE())
            {
                if (Get_state_ConcurrentCore(Get_que_CoreToLaunch(index_B)) == ptr_Global->Get_flag_core_IDLE())
                {
                    LaunchEnable_ShiftQueValues(index_A, index_B);
                }
                else if (Get_state_ConcurrentCore(Get_que_CoreToLaunch(index_B)) == ptr_Global->Get_flag_core_ACTIVE())
                {
                    if (Get_count_LaunchActive_For(index_A) > Get_count_LaunchActive_For(index_B))
                    {
                        LaunchEnable_ShiftQueValues(index_A, index_B);
                    }
                }
            }
            else if (Get_state_ConcurrentCore(Get_que_CoreToLaunch(index_A)) == ptr_Global->Get_flag_core_IDLE())

                if (Get_state_ConcurrentCore(Get_que_CoreToLaunch(index_B)) == ptr_Global->Get_flag_core_IDLE())
                {
                    if (Get_count_LaunchIdle_For(index_A) < Get_count_LaunchIdle_For(index_B))
                    {
                        LaunchEnable_ShiftQueValues(index_A, index_B);
                    }
                }
        }
    }
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::LaunchQue_Update(unsigned char number_Implemented_Cores)
{
    for (unsigned char index = 0; index < number_Implemented_Cores; index++)
    {
        switch (Get_state_ConcurrentCore(index))
        {
        case false:
        {
            Set_count_LaunchActive_For(index, 0);
            Set_count_LaunchIdle_For(index, Get_count_LaunchIdle_For(index) + 1);
            break;
        }
        case true:
        {
            Set_count_LaunchActive_For(index, Get_count_LaunchActive_For(index) + 1);
            Set_count_LaunchIdle_For(index, 0);
            break;
        }
        }
    }
}

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::DynamicStagger(unsigned char ptr_coreId)
{
    if (Get_concurrentCycle_Try_CoreId_Index() == ptr_coreId)
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

void Avril_FSD::ConcurrentQue_END_LaunchConcurrency_Control::LaunchEnable_ShiftQueValues(unsigned char concurrent_CoreId_A, unsigned char concurrent_CoreId_B)
{
    int temp_Int;// = new int(0);
    temp_Int = Get_count_LaunchActive_For(concurrent_CoreId_A);
    Set_count_LaunchActive_For(concurrent_CoreId_A, Get_count_LaunchActive_For(concurrent_CoreId_B));
    Set_count_LaunchActive_For(concurrent_CoreId_B, temp_Int);

    temp_Int = Get_count_LaunchIdle_For(concurrent_CoreId_A);
    Set_count_LaunchIdle_For(concurrent_CoreId_A, Get_count_LaunchIdle_For(concurrent_CoreId_B));
    Set_count_LaunchIdle_For(concurrent_CoreId_B, temp_Int);

    unsigned char temp_UnnsignedChar;// = new unsigned char(0);
    temp_UnnsignedChar = Get_que_CoreToLaunch(concurrent_CoreId_A);
    Set_que_CoreToLaunch(concurrent_CoreId_A, Get_que_CoreToLaunch(concurrent_CoreId_B));
    Set_que_CoreToLaunch(concurrent_CoreId_B, temp_UnnsignedChar);
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