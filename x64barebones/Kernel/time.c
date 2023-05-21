#include <time.h>
#include <interrupts.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

int milliseconds(){
	return MILLIS(ticks);
}

void holder(int time) {
  int startingTicks = ticks;
  while(ticks - startingTicks < time) {
    _hlt();
  }
}