#ifndef MEMORY_H
#define MEMORY_H

#include "machine.h"
#include "stdint.h"

#define MEM_MODE(i) (((i) >> 25) & 0x3)
#define MEM_SR1(i) (((i) >> 21) & 0xF)
#define MEM_SR2(i) ((i) & 0xF)
#define MEM_ADDR(i) (((i) >> 9) & 0xFFFF)

/* MOV (Move)
Transfers data to register
Modes:
    00 -> Register-Register
    01 -> Register-IMM32
    10 -> Register-Memory
*/
static inline void MOV(uint32_t i){
    //Checks if Register-IMM32 mode
    if (MEM_MODE(i))
    {
        reg[MEM_SR1(i)] = prog_read(++reg[RPC]);
    } // Checks if Register-Memory mode
    else if (MEM_MODE(i) >> 1)
    {
        reg[MEM_SR1(i)] = mem_read(++reg[RPC]);
    } // checks if Register-Register mode
    else if (MEM_MODE(i) == 0)
    {
        reg[MEM_SR1(i)] = reg[MEM_SR2(i)];
    }
}

/* STR (Store)
Stores data in memory
Modes:
    00 -> Memory-Register
    01 -> Memory-IMM32
    10 -> Memory-Memory
*/
static inline void STR(uint32_t i){
    //Checks if Memory-IMM32
    if (MEM_MODE(i))
    {
        mem_write(MEM_ADDR(i), prog_read(++reg[RPC]));
    } // Checks if Memory-Memory
    else if (MEM_MODE(i) >> 1)
    {
        mem_write(MEM_ADDR(i), mem_read(++reg[RPC]));
    }
    else if (MEM_MODE(i) == 0)
    {
        for(uint16_t j = 0; j < 5; j++){
            mem_write(MEM_ADDR(i) + j, LITTLE_ENDIAN_ENCODE(reg[MEM_SR2(i)], j));
        }
    }
}


static inline void PUSH(uint32_t i){}

static inline void POP(uint32_t i){}

#endif