#ifndef __PUSHALARM_H__
#define __PUSHALARM_H__

int g_buzzerpin;
int g_buttonpin;

void alarm_init(int buzzerpin, int buttonpin);
void alarm_on();
void alarm_off();
