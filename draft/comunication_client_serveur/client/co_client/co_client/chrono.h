#pragma once
#ifndef CHR


#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

void timer_start(std::function<void(void)> func, unsigned int att_ms);

#endif // !CHR


