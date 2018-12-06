#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

void timer(){
	puts("Hi");
}
int main(){
	timer_t timerID;

	struct sigevent         te;  
	struct itimerspec       its;  
	struct sigaction        sa;  
	int                     sigNo = SIGRTMIN;
	int			sec = 1;
	int			msec = 0;

	/* Set up signal handler. */  
	sa.sa_flags = SA_SIGINFO;  
	sa.sa_sigaction = timer;     // 타이머 호출시 호출할 함수 
	sigemptyset(&sa.sa_mask);  

	if (sigaction(sigNo, &sa, NULL) == -1)  
	{  
		printf("sigaction error\n");
		return -1;  
	}  

	/* Set and enable alarm */  
	te.sigev_notify = SIGEV_SIGNAL;  
	te.sigev_signo = sigNo;  
	te.sigev_value.sival_ptr = &timerID;  
	timer_create(CLOCK_REALTIME, &te, &timerID);  

	its.it_interval.tv_sec = sec;
	its.it_interval.tv_nsec = msec * 1000000;  
	its.it_value.tv_sec = sec;

	its.it_value.tv_nsec = msec * 1000000;
	timer_settime(timerID, 0, &its, NULL);

	while(1);

	return 0;
}
