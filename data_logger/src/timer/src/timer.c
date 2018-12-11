#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "timer.h"

timer_t timer_init(){
	timer_t timerID;

	return timerID;
}

void timer_deinit(){

}
void function_register(timer_t* timerID, void* function){

	struct sigevent         te;
	struct sigaction        sa;
	int                     sigNo = SIGRTMIN;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = function;     // 타이머 호출시 호출할 함수
	sigemptyset(&sa.sa_mask);

	if (sigaction(sigNo, &sa, NULL) == -1)
	{
		printf("sigaction error\n");
		return -1;
	}

	/* Set and enable alarm */
	te.sigev_notify = SIGEV_SIGNAL;
	te.sigev_signo = sigNo;
	te.sigev_value.sival_ptr = timerID;

	timer_create(CLOCK_REALTIME, &te, timerID);
}
void time_register(timer_t* timerID, int _sec, int _msec, int _interval){

	struct itimerspec       its;
	int			sec = _sec;
	int			msec = _msec;

	its.it_interval.tv_sec = sec;
	its.it_interval.tv_nsec = msec * _interval;
	its.it_value.tv_sec = sec;
	its.it_value.tv_nsec = msec * _interval;

	timer_settime(*timerID, 0, &its, NULL);
}

void run_timer(timer_t timerID, void* func, int _sec, int _msec, int _interval)
{
	function_register(&timerID, func);
	time_register(&timerID, _sec, _msec, _interval);
}
