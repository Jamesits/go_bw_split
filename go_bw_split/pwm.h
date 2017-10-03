#ifndef __PWM_H__
#define __PWM_H__

#include "msp430f149.h"

void Init_PWM();
void QEngine(unsigned int Left,unsigned int Right);
void HEngine(unsigned int Left,unsigned int Right);
#endif
