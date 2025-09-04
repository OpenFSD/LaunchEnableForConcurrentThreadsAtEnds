#include "ConcurrentQue_END_Framework.h"
#include "pch.h"

#include <cstddef>

class Avril_FSD::ConcurrentQue_END_LaunchConcurrency* ptr_LaunchConcurrency = NULL;

Avril_FSD::ConcurrentQue_END_Framework::ConcurrentQue_END_Framework()
{
	Create_ConcurrentQue();
}

Avril_FSD::ConcurrentQue_END_Framework::~ConcurrentQue_END_Framework()
{

}
Avril_FSD::ConcurrentQue_END_LaunchConcurrency* Avril_FSD::ConcurrentQue_END_Framework::Get_ConcurrentQue()
{
	return ptr_LaunchConcurrency;
}
void Avril_FSD::ConcurrentQue_END_Framework::Create_ConcurrentQue()
{
	Set_ConcurrentQue(new class Avril_FSD::ConcurrentQue_END_LaunchConcurrency());
	while (Get__ConcurrentQue() == NULL) { /* wait untill created */ }
	Get__ConcurrentQue()->Initialise_Control();
}
Avril_FSD::ConcurrentQue_END_LaunchConcurrency* Avril_FSD::ConcurrentQue_END_Framework::Get__ConcurrentQue()
{
	return ptr_LaunchConcurrency;
}
void Avril_FSD::ConcurrentQue_END_Framework::Set_ConcurrentQue(Avril_FSD::ConcurrentQue_END_LaunchConcurrency* concurrentQue)
{
	ptr_LaunchConcurrency = concurrentQue;
}