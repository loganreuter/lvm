#ifndef LOGICAL_H
#define LOGICAL_H

#include "stdint.h"
#include "machine.h"

#define LOG_SR1(i) (((i) >> 23) & 0xF)
#define LOG_SR2(i) ((i) & 0xF)

/* AND
*/
static inline void AND(uint32_t i){
    reg[LOG_SR1(i)] = reg[LOG_SR1(i)] * reg[LOG_SR2(i)];
    update_flag(LOG_SR1(i));
}
static inline void OR(uint32_t i) {
    reg[LOG_SR1(i)] = reg[LOG_SR1(i)] | reg[LOG_SR2(i)];
    update_flag(LOG_SR1(i));
}  
static inline void XOR(uint32_t i) {
    reg[LOG_SR1(i)] = reg[LOG_SR1(i)] ^ reg[LOG_SR2(i)];
    update_flag(LOG_SR1(i));
}
static inline void TEST(uint32_t i) {

}
static inline void NOT(uint32_t i) {
    reg[LOG_SR1(i)] = ~reg[LOG_SR2(i)];
    update_flag(LOG_SR1(i));
}

#endif