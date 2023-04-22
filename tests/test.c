#include "../lvm/lvm.h"
#include "test.h"

int main(){
    /* Test for the STI command:
    STI x0 x1
    Expected result: 1
    */
    TEST sti = new_test_blank();
    sti.name = "STI";
    sti.instr = &(uint32_t){0b00110000000000000000000000000001};
    sti.num_of_instr = 1;
    sti.expected = &(uint32_t){1};
    sti.found = &(uint32_t){mem_readn(0, 5)};

    test(&sti);
}