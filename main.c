#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "dray.h"

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

    fprintf(fp, "extern printf\n");
    fprintf(fp, "global main\n\n");

    fprintf(fp, "section .note.GNU-stack\n");
    fprintf(fp, "section .data\n");
    fprintf(fp, "fmt:    db \"%%ld\", 10, 0\n\n");

    fprintf(fp, "section .text\n");
    fprintf(fp, "main:\n");

    for (size_t i = 0; i < operations.size; i++) {
        if (operations.items[i] == PUSH) {
            fprintf(fp, "    ;; push %d\n", operands.items[i]);
            fprintf(fp, "    push %d\n", operands.items[i]);
        } else if (operations.items[i] == PLUS) {
            fprintf(fp, "    ;; add\n");
            fprintf(fp, "    pop rax\n");
            fprintf(fp, "    pop rbx\n");
            fprintf(fp, "    add rax, rbx\n");
            fprintf(fp, "    push rax\n");
        } else if (operations.items[i] == SUB) { 
            fprintf(fp, "    ;; sub\n");
            fprintf(fp, "    pop rax\n");
            fprintf(fp, "    pop rbx\n");
            fprintf(fp, "    sub rax, rbx\n");
            fprintf(fp, "    push rax\n");
        } else if (operations.items[i] == DUMP) {
            fprintf(fp, "    ;; print\n");
            fprintf(fp, "    pop rax\n");
            fprintf(fp, "    lea rdi, [rel fmt]\n");
            fprintf(fp, "    mov rsi, rax\n");
            fprintf(fp, "    xor rax, rax\n");
            fprintf(fp, "    call printf\n");
        } else {
            assert(0);
        }
    }

    fprintf(fp, "\n");
    fprintf(fp, "    mov rax, 60\n");
    fprintf(fp, "    mov rdi, 0\n");
    fprintf(fp, "    syscall\n");

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
