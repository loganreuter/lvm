/*
    Custom 32-bit Virtual Machine
    Harvard Architecture
    Register Based
    Author: Logan Reuter
*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../debug/debug.h"



/***************************
Op Codes

####    ###   #########################
OpCode  DR    Rest of the args

****************************/

//Macro that extracts the Op Code
// #define OPC(i) ((i) >> 27) //Extracts OpCode

// /*
// STORE (STR)
// */
// static inline void STR(uint32_t i){
//     // 0001 XXX KKKK....
//     reg[DR(i)] = mem_read(ADDR(i));
//     update_flag(DR(i));
// }

// /* Load Indirect:
// */
// static inline void LDI(uint32_t i){
//     DEBUG("LDI", "LDI %s x%x", reg_name(DR(i)), IMM24(i));

//     reg[DR(i)] = IMM24(i);

//     DEBUG("LDI", "%s = x%x", reg_name(DR(i)), reg[DR(i)]);

//     update_flag(DR(i));
// }
// static inline void STI(uint32_t i){
//     /*
//     0011 KKKK 0000 0000 0000 0000 0000
//     OP   ADDR 24-Bit Number
//     */
//     DEBUG("STI", "STI %x %x", ADDR(i), IMM24(i));

//     for(uint16_t j = 0; j < 5; j++){
//         mem_write(ADDR(i) + j, LITTLE_ENDIAN_ENCODE(i, j));
//         DEBUG("STI_MEM_WRITE","ADDR: %d = %x", ADDR(i) + j, mem_read(ADDR(i) + j));
//     }
// }





