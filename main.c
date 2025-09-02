#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "dray.h"
#include "builtins.h"

enum OPs {
    PUSH,
    PLUS,
    SUB,
    DUMP,
    OP_COUNT
};

Dray operations;
Dray operands;

void add_op(enum OPs op, int n) {
    append(&operations, op);
    append(&operands, n);
}

void populate_arr() {
    // TODO: add a full-on lexer to populate the array
    add_op(PUSH, 34);
    add_op(PUSH, 35);
    add_op(PLUS, 0);
    add_op(DUMP, 0);
    add_op(PUSH, 80);
    add_op(PUSH, 500);
    add_op(SUB, 0);
    add_op(DUMP, 0);
}

void simulate_program() {
    assert(OP_COUNT == 4);
    Dray st = construct(1);
    for (size_t i = 0; i < operations.size; i++) {
        if (operations.items[i] == PUSH) {
            append(&st, operands.items[i]);
        } else if (operations.items[i] == PLUS) {
            assert(st.size >= 2);

            int o1 = pop(&st);
            int o2 = pop(&st);

            append(&st, o1 + o2);
        } else if (operations.items[i] == SUB) {
            assert(st.size >= 2);

            int o1 = pop(&st);
            int o2 = pop(&st);

            append(&st, o1 - o2);
        } else if (operations.items[i] == DUMP) {
            assert(st.size >= 1);

            int o1 = st.items[st.size-1];
            pop(&st);

            printf("%d\n", o1);
        }
    }
}

void compile_program(char* path_to_file) {
    assert(OP_COUNT == 4);
    FILE *fp = fopen(path_to_file, "w");
    if (!fp) {
        perror("fopen");
        return;
    }

    prologue(fp);
    dump_code(fp);

    fprintf(fp, "_start:\n");

    for (size_t i = 0; i < operations.size; i++) {
        if (operations.items[i] == PUSH) {
            push_code(fp, operands.items[i]);
        } else if (operations.items[i] == PLUS) {
            plus_code(fp);
        } else if (operations.items[i] == SUB) { 
            sub_code(fp);
        } else if (operations.items[i] == DUMP) {
            print_code(fp);
        } else {
            assert(0);
        }
    }

    epilogue(fp);

    fclose(fp);
}


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("USAGE: stenga [sub-command]");
        return 1;
    }

    operations = construct(1);
    operands = construct(1);
    populate_arr();

    if (strcmp(argv[1], "sim") == 0) {
        simulate_program();
    } else if (strcmp(argv[1], "com") == 0) {
        compile_program("output.asm");
    }

    return 0;
}
