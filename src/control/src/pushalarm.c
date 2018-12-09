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
  digitalWrite(buzzerpin, HIGH);
}
void alarm_off(){
  if(digitalRead(buttonpin) == HIGH)
      digitalWrite(buzzerpin, LOW);
}

int main()
{
  alarm_init(15, 16);
  alarm_on();

  while(1){
    alarm_off();
  }

  return 0;
}
