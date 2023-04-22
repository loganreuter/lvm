#ifndef TEST_H
#define TEST_H

    #include <stdio.h>
    #include <stdint.h>
    #include "../lvm/lvm.h"
    #include "../debug/debug.h"

    typedef struct TEST{
        const char *name;
        uint32_t *instr;
        int num_of_instr;
        uint32_t *expected;
        uint32_t *found;
    } TEST;

    TEST new_test(const char *name, uint32_t *instr, int num_of_instr, uint32_t *expected, uint32_t *found)
    {
        TEST t;

        t.name = name;
        t.instr = instr;
        t.num_of_instr = num_of_instr;
        t.expected = expected;
        t.found = found;

        return t;
    }

    TEST new_test_blank(){
        TEST t;
        return t;
    }

    void test(TEST *t){
        printf("TEST_%s:\n", t->name);
        
        for(int i = 0; i < t->num_of_instr; i++){
            program[i] = t->instr[i];
        }

        start();

        if(*(t->expected) == *(t->found)){
            test_passed();
        } else {
            test_failed("Expected %x, Found %x", *(t->expected), *(t->found));
        }

        clear();
    }
#endif