#pragma once

namespace Avril_FSD
{
    class ConcurrentQue_END_Framework
    {
    public:
        ConcurrentQue_END_Framework();
        virtual ~ConcurrentQue_END_Framework();
        class ConcurrentQue_END_LaunchConcurrency* Get_ConcurrentQue();

    private:
        static void Create_ConcurrentQue();
        static class ConcurrentQue_END_LaunchConcurrency* Get__ConcurrentQue();
        static void Set_ConcurrentQue(class ConcurrentQue_END_LaunchConcurrency* concurrentQue);
    };
}