#include "../lvm/lvm.h"
#include "test.h"
#include "stdint.h"

static inline void mov_01_check(int *ret, uint32_t *res){
    *res = reg[EAX];
    *ret = *(res) == 69;
    DEBUG("mov_01_check", "RET %d\tRES x%x", *ret, *res);
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

    run(&mov_01);
}