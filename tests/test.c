#include "../lvm/lvm.h"
#include "test.h"
#include "stdint.h"

static inline void mov_01_check(int *ret, uint32_t *res){
    *res = reg[EAX];
    *ret = *(res) == 69;
    DEBUG("mov_01_check", "RET %d\tRES x%x", *ret, *res);
}
static inline void str_01_check(int *ret, uint32_t *res){
    *res = mem_readn(0, 4);
    *ret = *(res) == 69;
    DEBUG("str_01_check", "RET %d\tRES x%x", *ret, *res);
}
static inline void mov_10_check(int *ret, uint32_t *res){
    *res = reg[EAX];
    *ret = *(res) == 69;
    DEBUG("mov_10_check", "RET %d\tRES x%x", *ret, *res);
}

int main(){

    /* Test MOV (Mode 01)
    MOV 01 EAX x45
    Expected result: 69
    */
    uint32_t mov_01_instr[2] = {
        0x02000000, //MOV MODE(01) EAX
        0x00000045, //69
    };
    Test mov_01 = new_test_blank();
    mov_01.name = "MOV 01";
    mov_01.desc = "Checks if MOV (set to Mode 01) stores the correct value in the correct register";
    mov_01.instr = mov_01_instr;
    mov_01.num_of_instr = 2;
    mov_01.check = mov_01_check;

    /* Test STR (Mode 01)
    STR 01 0x0 x45
    Expected Result: 69
    */
   uint32_t str_01_instr[2] = {
    0x0a000000,
    0x45,
   };
   Test str_01 = new_test_blank();
   str_01.name = "STR 01";
   str_01.desc = "Checks if STR (set to Mode 01) stores the correct value in the memory address";
   str_01.instr = str_01_instr;
   str_01.num_of_instr = 2;
   str_01.check = str_01_check;

    /* Test MOV (Mode 10)
    Stores 69 in memory address 0x0
    Loads value from memory into register EAX
    */
    uint32_t mov_10_instr[4] = {
        0x0a000000, //Store 69 into memory address 0
        0x45,       //69
        0x04000000, //Move value of memory address 0 into EAX
        0x0         //memory address 0
    };
    Test mov_10 = new_test_blank();
    mov_10.name = "MOV 01";
    mov_10.desc = "Check if MOV (set to Mode 10) loads the right value from memory and stores it in the correct register";
    mov_10.instr = mov_10_instr;
    mov_10.num_of_instr = 4;
    mov_10.check = mov_10_check;

    run(&mov_01);
    run(&mov_10);
    run(&str_01);
}