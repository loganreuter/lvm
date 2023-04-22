#include "../lvm/lvm.h"
#include "test.h"

static inline void sti_check(int *ret, uint32_t *res){
    *res = mem_readn(0, 5);
    DEBUG("sti_check", "RET %d", *ret);
    *ret = *(res) == 1;
}

int main(){
    /* Test for the STI command:
    STI x0 x1
    Expected result: 1
    */
    TEST sti = new_test_blank();
    sti.name = "STI";
    sti.desc = "Checks if STI stores a value in the right memory location";
    sti.instr = &(uint32_t){0b00110000000000000000000000000001};
    sti.num_of_instr = 1;
    sti.check = sti_check;

    test(&sti);
}