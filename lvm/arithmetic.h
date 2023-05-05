#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "machine.h"
#include "stdint.h"

#define SR1(i) (((i) >> 21) & 0x7) // First source register
#define SR2(i) (((i) >> 18) & 0x7) // Second source register
#define ADDR(i) (((i) >> 21) & 0xF)
#define LITTLE_ENDIAN_ENCODE(i, s) (((i) >> (s * 4)) & 0xFF)

// define the number of operations

/* ARITHMETIC OPERATIONS */
#define ARTH_MODE(i) (((i) >> 26) & 0x1)

/* ADD (addition)
Modes
0: Adds two registers together (ADD)
1: Adds a register and 32-bit number together (IADD)
*/
static inline void ADD(uint32_t i) {
    reg[SR1(i)] = reg[SR1(i)] + (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[SR2(i)];
    update_flag(SR1(i));
}

/* SUB (subtraction)

*/
static inline void SUB(uint32_t i)
{
    reg[SR1(i)] = reg[SR1(i)] - (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[SR2(i)];
    update_flag(SR1(i));
}

/* MUL (multiplication)
 */
static inline void MUL(uint32_t i)
{
    reg[SR1(i)] = reg[SR1(i)] * (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[SR2(i)];
    update_flag(SR1(i));
}

/* DIV (division)
 */
static inline void DIV(uint32_t i)
{
    reg[SR1(i)] = reg[SR1(i)] / (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[SR2(i)];
    update_flag(SR1(i));
}

/* MOD (modulus/remainder)
 */
static inline void MOD(uint32_t i)
{
    reg[SR1(i)] = reg[SR1(i)] % (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[SR2(i)];
    update_flag(SR1(i));
}

#endif