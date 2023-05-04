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

#define MEMORY_MAX (1 << 16)
const uint32_t DS_START = 0x0100;
const uint32_t HEAP_START = 0x1000;
const uint32_t STACK_START = 0xFFFF;

uint32_t program[MEMORY_MAX]; // Holds the instructions
uint8_t memory[MEMORY_MAX]; // Holds the data

static inline uint32_t prog_read(uint32_t address){ return program[address]; }
// static inline void i_write(uint32_t address, uint32_t val){ return program[address] = val; }

static inline uint8_t mem_read(uint16_t address){ return memory[address]; }
static inline uint32_t mem_readn(uint16_t address, int n) {
    uint32_t val = 0;
    for(int i = 0; i < n; i++){
        val = (mem_read(address + i) << 4*i) | val;
    }
    return val;
}
static inline void mem_write(uint16_t address, uint8_t val) { memory[address] = val;}

/* Registers
    R0-R7 -> General Purpose Registers
    ESP -> Stack Pointer Register

*/
#define NUM_REGISTERS (16)
enum regist{
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
};
uint32_t reg[NUM_REGISTERS];
char *reg_name(enum regist r){
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

enum flags {CF = 0 << 0, PF = 0 << 2, AF = 0 << 4, ZF = 0 << 6, SF = 0 << 7, TF = 0 << 8, IF = 0 << 9, DF = 0 << 10, OF = 0 << 11 };
static inline void update_flag(enum regist r){
    if (reg[r] == 0)
        reg[FLAG] = ZF;
}

void clear_memory(){
    memset(memory, 0, sizeof(memory));
}
void clear_program(){
    memset(program, 0, sizeof(program));
}
void clear_registers(){
    memset(reg, 0, sizeof(reg));
}
void clear(){
    clear_memory();
    clear_program();
    clear_registers();
}

/***************************
Op Codes

####    ###   #########################
OpCode  DR    Rest of the args

****************************/

//Macro that extracts the Op Code
#define OPC(i) ((i) >> 27) //Extracts OpCode
#define SR1(i) (((i) >> 21) & 0x7) //First source register
#define SR2(i) (((i)>>18) & 0x7) //Second source register
#define ADDR(i) (((i)>>21) & 0xF)
#define IMM16(i) ((i) & 0xFFFF) //Immediate 16-bit number
#define LITTLE_ENDIAN_ENCODE(i, s) (((i) >> (s*4))&0xFF)

//define the number of operations
#define NOPS (16)
typedef void (*op_ex_f)(uint32_t instruction);

/* ARITHMETIC OPERATIONS */
#define ARTH_MODE(i) (((i) >> 26) & 0x1)

/* ADD (addition)
Modes
0: Adds two registers together (ADD)
1: Adds a register and 32-bit number together (IADD)
*/
static inline void ADD(uint32_t i){
    reg[SR1(i)] = reg[SR1(i)] + (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[SR2(i)];
    update_flag(SR1(i));
}

/* SUB (subtraction)

*/
static inline void SUB(uint32_t i){
    reg[SR1(i)] = reg[SR1(i)] - (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[SR2(i)];
    update_flag(SR1(i));
}

/* MUL (multiplication)
*/
static inline void MUL(uint32_t i){
    reg[SR1(i)] = reg[SR1(i)] * (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[SR2(i)];
    update_flag(SR1(i));
}

/* DIV (division)
*/
static inline void DIV(uint32_t i){
    reg[SR1(i)] = reg[SR1(i)] / (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[SR2(i)];
    update_flag(SR1(i));
}

/* MOD (modulus/remainder)
*/
static inline void MOD(uint32_t i){
    reg[SR1(i)] = reg[SR1(i)] % (ARTH_MODE(i)) ? prog_read(++reg[RPC]) : reg[SR2(i)];
    update_flag(SR1(i));
}

/*
STORE (STR)
*/
static inline void STR(uint32_t i){
    // 0001 XXX KKKK....
    reg[DR(i)] = mem_read(ADDR(i));
    update_flag(DR(i));
}

/* Load Indirect:
*/
static inline void LDI(uint32_t i){
    DEBUG("LDI", "LDI %s x%x", reg_name(DR(i)), IMM24(i));

    reg[DR(i)] = IMM24(i);

    DEBUG("LDI", "%s = x%x", reg_name(DR(i)), reg[DR(i)]);

    update_flag(DR(i));
}
static inline void STI(uint32_t i){
    /*
    0011 KKKK 0000 0000 0000 0000 0000
    OP   ADDR 24-Bit Number
    */
    DEBUG("STI", "STI %x %x", ADDR(i), IMM24(i));

    for(uint16_t j = 0; j < 5; j++){
        mem_write(ADDR(i) + j, LITTLE_ENDIAN_ENCODE(i, j));
        DEBUG("STI_MEM_WRITE","ADDR: %d = %x", ADDR(i) + j, mem_read(ADDR(i) + j));
    }
}

op_ex_f op_ex[NOPS] = {
    ADD,
    STR,
    LDI,
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



