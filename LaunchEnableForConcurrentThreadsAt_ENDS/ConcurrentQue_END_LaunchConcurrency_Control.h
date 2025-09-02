#pragma once
#include <array>
#include <vector>

namespace Avril_FSD
{
    class ConcurrentQue_END_LaunchConcurrency_Control
    {
    public:
        ConcurrentQue_END_LaunchConcurrency_Control(class ConcurrentQue_END_Global* ptr_Global, unsigned char number_Implemented_Cores);
        virtual ~ConcurrentQue_END_LaunchConcurrency_Control();

        void LaunchEnable_Activate(class ConcurrentQue_END_Global* ptr_Global);
        void LaunchEnable_Request(unsigned char concurrent_CoreId, class ConcurrentQue_END_Global* ptr_Global);
        void LaunchEnable_SortQue(class ConcurrentQue_END_Global* ptr_Global, unsigned char number_Implemented_Cores);
        void LaunchQue_Update(unsigned char number_Implemented_Cores);

        unsigned char Get_concurrentCycle_Try_CoreId_Index();
        unsigned char Get_flag_CoreId_Of_CoreToLaunch();
        bool Get_flag_praisingLaunch();
        unsigned char Get_new_concurrentCycle_Try_CoreId_Index();
        bool Get_state_ConcurrentCore(unsigned char concurrent_CoreId);
        unsigned char Get_que_CoreToLaunch(unsigned char index);

        void Set_concurrentCycle_Try_CoreId_Index(unsigned char concurrentCycle_Try_CoreId_Index);
        void Set_flag_praisingLaunch(bool flag_praisingLaunch);
        void Set_new_concurrentCycle_Try_CoreId_Index(unsigned char new_concurrentCycle_Try_CoreId_Index);
        void Set_state_ConcurrentCore(bool state_ConcurrentCore, unsigned char concurrent_CoreId);

    protected:

    private:
        void DynamicStagger(unsigned char ptr_coreId);
        void LaunchEnable_ShiftQueValues(unsigned char concurrent_CoreId_A, unsigned char concurrent_CoreId_B);
        
        int Get_count_LaunchActive_For(unsigned char concurrent_CoreId);
        int Get_count_LaunchIdle_For(unsigned char concurrent_CoreId);
        std::vector<unsigned char>* Get_stack_PriseEventId();
        
        void Set_count_LaunchActive_For(int count_LaunchActive_For, unsigned char concurrent_CoreId);
        void Set_count_LaunchIdle_For(int count_LaunchIdle_For, unsigned char concurrent_CoreId);
        void Set_stack_PriseEventId(std::vector<unsigned char>* stack_PriseEventId);
        void Set_que_CoreToLaunch(unsigned char que_CoreToLaunch, unsigned char index);
    };
}