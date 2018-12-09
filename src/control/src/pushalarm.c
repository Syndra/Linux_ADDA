#include <stdio.h>
#include <wiringPi.h>
#include "pushalarm.h"

void alarm_init(int buzzerpin, int buttonpin){

  g_buzzerpin = buzzerpin;
  g_buttonpin = buttonpin;

  wiringPiSetup () ;
  pinMode (buzzerpin, OUTPUT) ;
  pinMode (buttonpin, INPUT) ;
}
void alarm_on(){
  digitalWrite(g_buzzerpin, HIGH);
  printf("on\n");
}
int alarm_off(){
  if(digitalRead(g_buttonpin) == HIGH){
      digitalWrite(g_buzzerpin, LOW);
      printf("off\n");
      return 1;
    }
    return 0;
}

int main()
{
  alarm_init(29, 28);
  alarm_on();

  while(!alarm_off());

  return 0;
}
