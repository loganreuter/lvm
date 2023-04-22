#include "../lvm/lvm.h"
#include <stdio.h>

void test_sti(){
    program[0] = 0x20000001; // 0010 0000 000000000000000000000001 (STI $0000 1)

    start();

    printf("test_sti:\n");
    uint32_t val = 0;
    for(uint16_t i = 0; i < 5; i++){
        val = mem_read(i) << (4*i) | val;
        printf("\tADDR: %x \t VALUE: %x\n", i, val);
    }
    printf("\t%x\n", val);
}