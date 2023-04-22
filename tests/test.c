#include "../lvm/lvm.h"
#include "test.h"

static inline void ldi_check(int *ret, uint32_t *res){
    DEBUG("ldi_check", "R2 = x%x", reg[R2]);
    *res = reg[R2];
    *ret = *(res) == 69;
    DEBUG("ldi_check", "RET %d RES x%x", *ret, *res);
}

static inline void sti_check(int *ret, uint32_t *res){
    *res = mem_readn(0, 5);
    *ret = *(res) == 1;
    DEBUG("sti_check", "RET %d RES x%x", *ret, *res);
}

int main(){

    /* Test LDI command
    LDI x0 x45
    Expected result: 69
    */
    TEST ldi = new_test_blank();
    ldi.name = "LDI";
    ldi.desc = "Checks if LDI stores the correct value in the correct register";
    ldi.instr = &(uint32_t){0b00100010000000000000000001000101};
    ldi.num_of_instr = 1;
    ldi.check = ldi_check;

    /* Test for the STI command:
    STI x0 x1
    Expected result: 1
    */
    TEST sti = new_test_blank();
    sti.name = "STI";
    sti.desc = "Checks if STI stores the correct value in the correct memory location";
    sti.instr = &(uint32_t){0b00110000000000000000000000000001};
    sti.num_of_instr = 1;
    sti.check = sti_check;

    test(&ldi);
    test(&sti);
}