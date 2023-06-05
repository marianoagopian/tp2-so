// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdint.h>
#include <speaker.h>
#include <interrupts.h>

void beep(uint32_t nFrequence) {
  _beep_start(1193180 / nFrequence);
}

void noSound() {
  _beep_stop();
}