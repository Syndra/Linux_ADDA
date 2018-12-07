#ifndef __TIMER_H__
#define __TIMER_H__
#include <signal.h>
#include <time.h>
#include <unistd.h>

timer_t timer_init();
void timer_deinit();
void function_register(timer_t* timerID, void* function);
void time_register(timer_t* timerID, int _sec, int _msec, int _interval);
void timer();
#endif
