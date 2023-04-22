/*
    Custom 32-bit Virtual Machine
    Harvard Architecture
    Register Based
    Author: Logan Reuter
*/
#include <stdio.h>
#include <stdint.h>
#include "../debug/debug.h"

#define MEMORY_MAX (1 << 16)
const uint32_t DS_START = 0x0100;
const uint32_t HEAP_START = 0x1000;
const uint32_t STACK_START = 0xFFFF;

uint32_t program[MEMORY_MAX]; // Holds the instructions
uint8_t memory[MEMORY_MAX]; // Holds the data

static inline uint32_t prog_read(uint32_t address){ return program[address]; }
// static inline void i_write(uint32_t address, uint32_t val){ return program[address] = val; }

static inline uint8_t mem_read(uint16_t address){ return memory[address]; }
static inline void mem_write(uint16_t address, uint8_t val) { memory[address] = val;}

/*
Registers
    R0-R7 -> General Purpose Registers
    ESP -> Stack Pointer Register

*/
enum regist{
    R0 = 0,
    R1,
    R2,
    R3,
    R4,
    R5,
    R6,
    R7,
    ESP,
    RPC,
    RCND,
    RCNT
};
uint32_t reg[RCNT];
char *reg_name(enum regist r){
    switch (r)
    {
    case R0:
        return "R0";
    case R1:
        return "R1";
    case R2:
        return "R2";
    case R3:
        return "R3";
    case R4:
        return "R4";
    case R5:
        return "R5";
    case R6:
        return "R6";
    case R7:
        return "R7";
    case ESP:
        return "ESP";
    case RPC:
        return "RPC";
    case RCND:
        return "RCND";
    case RCNT:
        return "RCNT";
    default:
        return "INVALID";
    }
}

enum flags {FL_POS = 1 << 0, FL_ZRO = 1 << 1, FL_NEG = 1 << 2};
static inline void update_flag(enum regist r){
    if (reg[r] == 0)
        reg[RCND] = FL_ZRO;
    else if (reg[r] >> 15)
        reg[RCND] = FL_NEG;
    else
        reg[RCND] = FL_POS;
}


/***************************
Op Codes

####    ###   #########################
OpCode  DR    Rest of the args

****************************/

//Macro that extracts the Op Code
#define OPC(i) ((i) >> 28) //Extracts OpCode
#define DR(i) (((i)>>25) & 0x7) //Extracts the Destination Register (DR)
#define SR1(i) (((i)>>21) & 0x7)
#define SR2(i) (((i)>>18) & 0x7)
#define ADDR(i) (((i)>>21) & 0xF)
#define IMM24(i) ((i) & 0xFFFFFF) //Extracts the final 24 bits from an instruction
#define LITTLE_ENDIAN_ENCODE(i, s) (((i) >> (s*4))&0xFF)

//define the number of operations
#define NOPS (16)
typedef void (*op_ex_f)(uint32_t instruction);

static inline void ADD(uint32_t i){
    reg[DR(i)] = reg[SR1(i)] + reg[SR2(i)];
    update_flag(DR(i));
}
static inline void LD(uint32_t i){
    //0001 XXX KKKK....
    reg[DR(i)] = mem_read(ADDR(i));
    update_flag(DR(i));
}
static inline void STI(uint32_t i){
    /*
    0010 KKKK 0000 0000 0000 0000 0000
    OP   ADDR 24-Bit Number
    */
    DEBUG("STI %x %x", ADDR(i), IMM24(i));

    for(uint16_t j = 0; j < 5; j++){
        mem_write(ADDR(i) + j, LITTLE_ENDIAN_ENCODE(i, j));
        DEBUG("\tADDR: %d = %x\n", ADDR(i) + j, LITTLE_ENDIAN_ENCODE(i, j));
    }
}

op_ex_f op_ex[NOPS] = {
    ADD,
    LD,
    STI
};

void start(){
    reg[RPC] = 0x0;
    int size = 3;

    while(reg[RPC] < size){
       uint32_t i = prog_read(reg[RPC]++);

       op_ex[OPC(i)](i); 
    }
}



