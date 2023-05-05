#ifndef LVM_H
#define LVM_H

#include "machine.h"

//Various operation definition
#include "memory.h"
#include "arithmetic.h"

#define NOPS (16)
typedef void (*op_ex_f)(uint32_t instruction);

op_ex_f op_ex[NOPS] = {
    MOV,
    STR,
    ADD,
};

void start()
{
    reg[RPC] = 0x0;
    int size = 3;

    while (reg[RPC] < size)
    {
        uint32_t i = prog_read(reg[RPC]++);

        op_ex[OPC(i)](i);
    }
}

#endif