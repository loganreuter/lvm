#include "../lvm/lvm.h"
#include <stdio.h>

void test_add(){
    program[0] = 0x20000001; // 0010 0000 000000000000000000000001 (STR $0000 1)
    program[1] = 0x80; //0001 000 0000 (LD R0 $0000)
    program[2] = 0x40; //0000 001 000 000 (ADD R1 R0 R0)

    start();

    printf("test_add:\n");
    printf("\tTest 1: ");
    if(mem_read(0) != 1){
        printf("FAILED\n\t\tExpected value %d, found value %d\n", 1, mem_read(0));
    }else {
        printf("PASSED\n");
    }

    printf("\tTest 2: ");
    if(reg[R0] != 1){
        printf("FAILED\n\t\tExpected value %d, found value %d\n", 1, reg[R0]);
    } else {
        printf("PASSED\n");
    }

    printf("\tTest 3: ");
    if(reg[R1] != 2){
        printf("FAILED\n\t\tExpected value %d, found value %d\n", 2, reg[R1]);
    }
}