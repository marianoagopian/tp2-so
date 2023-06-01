#ifndef LOCKS_H_
#define LOCKS_H_

#include "./lib.h"

void lock(unsigned int * lock);
void unlock(unsigned int * lock);

#endif