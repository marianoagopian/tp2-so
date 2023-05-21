#ifndef _TIME_H_
#define _TIME_H_

#define MILLIS(x) ((x) * 55)

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();

int milliseconds();

void holder(int time);

#endif
