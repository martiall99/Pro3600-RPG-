#include "chrono.h"


void timer_start(std::function<void(void)> func, unsigned int att_ms)
{
	std::thread(
		[func,att_ms]() //on capture toutes les varaibles 
	{
		while (true)
		{
			func();
			std::this_thread::sleep_for(std::chrono::milliseconds(att_ms));
		}
	}
	).detach();
}
