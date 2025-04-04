// WaitLaunch_Client_ConcurrentThread_lib
// // dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) void Create_ConcurrentQue()
{
    ConcurrentQue::ConcurrentQue_Client_Framework::Create_ConcurrentQue();
}
extern "C" __declspec(dllexport) void Request_Wait_Launch(unsigned char concurrent_CoreId)
{
    ConcurrentQue::ConcurrentQue_Client_Framework::Request_Wait_Launch(concurrent_CoreId);
}
extern "C" __declspec(dllexport) void Thread_End(unsigned char concurrent_CoreId)
{
    ConcurrentQue::ConcurrentQue_Client_Framework::Thread_End(concurrent_CoreId);
}
extern "C" __declspec(dllexport) __int8 Get_coreId_To_Launch()
{
    return ConcurrentQue::ConcurrentQue_Client_Framework::Get_coreId_To_Launch();
}
extern "C" __declspec(dllexport) bool Get_Flag_Active()
{
    return ConcurrentQue::ConcurrentQue_Client_Framework::Get_Flag_Active();
}
extern "C" __declspec(dllexport) bool Get_Flag_Idle()
{
    return ConcurrentQue::ConcurrentQue_Client_Framework::Get_Flag_Idle();
}
extern "C" __declspec(dllexport) bool Get_State_LaunchBit()
{
    return ConcurrentQue::ConcurrentQue_Client_Framework::Get_State_LaunchBit();
}