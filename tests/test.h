#ifndef TEST_H
#define TEST_H

    #include <stdio.h>
    #include <stdint.h>
    #include "../lvm/lvm.h"
    #include "../debug/debug.h"

    typedef void (*Check)(int *ret, uint32_t *found);
    typedef struct TEST{
        const char *name;
        const char *desc;
        uint32_t *instr;
        int num_of_instr;
        Check check;
        int expect;
    } TEST;

    TEST new_test(const char *name, uint32_t *instr, int num_of_instr, int expect, Check check)
    {
        TEST t;

        t.name = name;
        t.instr = instr;
        t.num_of_instr = num_of_instr;
        t.expect = expect;
        t.check = check;

        return t;
    }

    TEST new_test_blank(){
        TEST t;
        return t;
    }

    void test(TEST *t){
        printf("TEST_%s:\n%s\n", t->name, t->desc);

        start(t->instr, t->num_of_instr);

        int cond = 5;
        uint32_t found;
        t->check(&cond, &found);

        DEBUG("test", "COND: %d", cond);

        if (cond == 1){
            test_passed();
        } else {
            test_failed("Expected %x, Found %x", t->expect, found);
        }

        clear();
    }
#endif