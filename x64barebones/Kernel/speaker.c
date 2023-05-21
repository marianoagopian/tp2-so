#include <stdint.h>
#include <speaker.h>
#include <interrupts.h>

void beep(uint32_t nFrequence) {
  _beep_start(1193180 / nFrequence);
}

void noSound() {
  _beep_stop();
}