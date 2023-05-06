#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "machine.h"
#include "stdint.h"

#define ARTH_SR1(i) (((i) >> 21) & 0xF) // First source register
#define ARTH_SR2(i) (((i) >> 18) & 0xF) // Second source register

/* ARITHMETIC OPERATIONS */
#define ARTH_MODE(i) (((i) >> 26) & 0x1)

/* ADD (addition)
Modes
0: Adds two registers together (ADD)
1: Adds a register and 32-bit number together (IADD)
*/
static inline void ADD(uint32_t i) {
    reg[ARTH_SR1(i)] = reg[ARTH_SR1(i)] + (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[ARTH_SR2(i)];
    update_flag(ARTH_SR1(i));
}

/* SUB (subtraction)

*/
static inline void SUB(uint32_t i)
{
    reg[ARTH_SR1(i)] = reg[ARTH_SR1(i)] - (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[ARTH_SR2(i)];
    update_flag(ARTH_SR1(i));
}

/* MUL (multiplication)
 */
static inline void MUL(uint32_t i)
{
    reg[ARTH_SR1(i)] = reg[ARTH_SR1(i)] * (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[ARTH_SR2(i)];
    update_flag(ARTH_SR1(i));
}

/* DIV (division)
 */
static inline void DIV(uint32_t i)
{
    reg[ARTH_SR1(i)] = reg[ARTH_SR1(i)] / (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[ARTH_SR2(i)];
    update_flag(ARTH_SR1(i));
}

/* MOD (modulus/remainder)
 */
static inline void MOD(uint32_t i)
{
    reg[ARTH_SR1(i)] = reg[ARTH_SR1(i)] % (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[ARTH_SR2(i)];
    update_flag(ARTH_SR1(i));
}

/* INC (Increment)
*/
static inline void INC(uint32_t i)
{
    reg[ARTH_SR1(i)]++;
    update_flag(ARTH_SR1(i));
}

/* DEC (Decrement)
*/
static inline void DEC(uint32_t i)
{
    reg[ARTH_SR1(i)]--;
    update_flag(ARTH_SR1(i));
}

#endif