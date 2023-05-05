#ifndef MEMORY_H
#define MEMORY_H

#include "machine.h"
#include "stdint.h"

#define MODE(i) (((i) >> 25) & 0x3)
#define SR1(i) (((i) >> 21) & 0xF)

/* MOV (Move)
Transfers data to register
Modes:
    00 -> Register-Register
    01 -> Register-IMM32
    10 -> Register-Memory
*/
static inline void MOV(uint32_t i){}

/* STR (Store)
Stores data in memory
Modes:
*/
static inline void STR(uint32_t i){}

#endif