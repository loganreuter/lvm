#ifndef LVM_H
#define LVM_H

#include "machine.h"

//Various operation definition
#include "memory.h"
#include "arithmetic.h"
#include "logical.h"

#define NOPS (16)
typedef void (*op_ex_f)(uint32_t instruction);

op_ex_f op_ex[NOPS] = {
    MOV,
    STR,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    INC,
    DEC,
    AND,
    OR,
    XOR,
    TEST,
    NOT,
};

void start(uint32_t *ops, int size)
{
    //loads instructions into memory
    for(int i = 0; i < size; i++){
        program[i] = *(ops++);
    }

    reg[RPC] = 0x0;
    reg[CS] = CS_START;
    reg[DS] = DS_START;
    reg[HS] = HEAP_START;
    reg[SS] = STACK_START;
    reg[ESP] = STACK_START;

    while (reg[RPC] < size)
    {
        uint32_t i = prog_read(reg[RPC]++);

        op_ex[OPC(i)](i);
    }
}

#endif