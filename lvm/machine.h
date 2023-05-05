#ifndef MACHINE_H
#define MACHINE_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../debug/debug.h"

#define MEMORY_MAX (1 << 16)
const uint32_t DS_START = 0x0100;
const uint32_t HEAP_START = 0x1000;
const uint32_t STACK_START = 0xFFFF;

uint32_t program[MEMORY_MAX]; // Holds the instructions
uint8_t memory[MEMORY_MAX];   // Holds the data

static inline uint32_t prog_read(uint32_t address) { return program[address]; }
// static inline void i_write(uint32_t address, uint32_t val){ return program[address] = val; }

static inline uint8_t mem_read(uint16_t address) { return memory[address]; }
static inline uint32_t mem_readn(uint16_t address, int n)
{
    uint32_t val = 0;
    for (int i = 0; i < n; i++)
    {
        val = (mem_read(address + i) << 4 * i) | val;
    }
    return val;
}
static inline void mem_write(uint16_t address, uint8_t val) { memory[address] = val; }

/* Registers
    R0-R7 -> General Purpose Registers
    ESP -> Stack Pointer Register

*/
enum regist
{
    EAX,
    EBX,
    ECX,
    EDX,
    EEX,
    EFX,
    RPC,
    ESP,
    EBP,
    ESI,
    EDI,
    FLAG,
    CS,
    DS,
    HS,
    SS,
    REG_CNT
};
uint32_t reg[REG_CNT];
char *reg_name(enum regist r)
{
    switch (r)
    {
    case EAX:
        return "EAX";
    case EBX:
        return "EBX";
    case ECX:
        return "ECX";
    case EDX:
        return "EDX";
    case EEX:
        return "EEX";
    case EFX:
        return "EFX";
    case RPC:
        return "RPC";
    case ESP:
        return "ESP";
    case EBP:
        return "EBP";
    case ESI:
        return "ESI";
    case EDI:
        return "EDI";
    case FLAG:
        return "FLAG";
    case CS:
        return "CS";
    case DS:
        return "DS";
    case HS:
        return "HS";
    case SS:
        return "SS";
    default:
        return "INVALID";
    }
}

enum flags
{
    CF = 0 << 0,
    PF = 0 << 2,
    AF = 0 << 4,
    ZF = 0 << 6,
    SF = 0 << 7,
    TF = 0 << 8,
    IF = 0 << 9,
    DF = 0 << 10,
    OF = 0 << 11
};
static inline void update_flag(enum regist r)
{
    if (reg[r] == 0)
        reg[FLAG] = ZF;
}

void clear_memory()
{
    memset(memory, 0, sizeof(memory));
}
void clear_program()
{
    memset(program, 0, sizeof(program));
}
void clear_registers()
{
    memset(reg, 0, sizeof(reg));
}
void clear()
{
    clear_memory();
    clear_program();
    clear_registers();
}

#define OPC(i) ((i) >> 27) //Extracts OpCode

#endif