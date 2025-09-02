#include "pch.h"
#include <cstddef>

bool _flag_core_ACTIVE = NULL;
bool _flag_core_IDLE = NULL;
unsigned char _number_Implemented_Cores = NULL;

Avril_FSD::ConcurrentQue_END_Global::ConcurrentQue_END_Global()
{
    Set_flag_core_ACTIVE(bool(true));
    Set_flag_core_IDLE(bool(false));
    Set_number_Implemented_Cores(unsigned char(4));//NUMBER OF CORES
}
Avril_FSD::ConcurrentQue_END_Global::~ConcurrentQue_END_Global()
{

}
bool Avril_FSD::ConcurrentQue_END_Global::Get_flag_core_ACTIVE()
{
    return _flag_core_ACTIVE;
}
bool Avril_FSD::ConcurrentQue_END_Global::Get_flag_core_IDLE()
{
    return _flag_core_IDLE;
}
unsigned char Avril_FSD::ConcurrentQue_END_Global::Get_number_Implemented_Cores()
{
    return _number_Implemented_Cores;
}
void Avril_FSD::ConcurrentQue_END_Global::Set_flag_core_ACTIVE(bool flag_core_ACTIVE)
{
    _flag_core_ACTIVE = flag_core_ACTIVE;
}
void Avril_FSD::ConcurrentQue_END_Global::Set_flag_core_IDLE(bool flag_core_IDLE)
{
    _flag_core_IDLE = flag_core_IDLE;
}
void Avril_FSD::ConcurrentQue_END_Global::Set_number_Implemented_Cores(__int8 number_Implemented_Cores)
{
    _number_Implemented_Cores = number_Implemented_Cores;
}