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

    // dump new
    fprintf(fp, "section .text\n");
    fprintf(fp, "global _start\n");
    fprintf(fp, "dump:\n");
    fprintf(fp, "        movsx   rsi, edi\n");
    fprintf(fp, "        sub     rsp, 40\n");
    fprintf(fp, "        test    esi, esi\n");
    fprintf(fp, "        je      .L8\n");
    fprintf(fp, "        mov     ecx, esi\n");
    fprintf(fp, "        xor     eax, eax\n");
    fprintf(fp, ".L3:\n");
    fprintf(fp, "        movsx   rdx, ecx\n");
    fprintf(fp, "        lea     edi, [rax+rax*4]\n");
    fprintf(fp, "        mov     eax, ecx\n");
    fprintf(fp, "        imul    rdx, rdx, 1717986919\n");
    fprintf(fp, "        sar     eax, 31\n");
    fprintf(fp, "        sar     rdx, 34\n");
    fprintf(fp, "        sub     edx, eax\n");
    fprintf(fp, "        lea     eax, [rdx+rdx*4]\n");
    fprintf(fp, "        add     eax, eax\n");
    fprintf(fp, "        sub     ecx, eax\n");
    fprintf(fp, "        lea     eax, [rcx+rdi*2]\n");
    fprintf(fp, "        mov     ecx, edx\n");
    fprintf(fp, "        test    edx, edx\n");
    fprintf(fp, "        jne     .L3\n");
    fprintf(fp, "        test    eax, eax\n");
    fprintf(fp, "        je      .L4\n");
    fprintf(fp, "        mov     ecx, 1\n");
    fprintf(fp, ".L5:\n");
    fprintf(fp, "        movsx   rdx, eax\n");
    fprintf(fp, "        mov     edi, eax\n");
    fprintf(fp, "        imul    rdx, rdx, 1717986919\n");
    fprintf(fp, "        sar     edi, 31\n");
    fprintf(fp, "        sar     rdx, 34\n");
    fprintf(fp, "        sub     edx, edi\n");
    fprintf(fp, "        lea     edi, [rdx+rdx*4]\n");
    fprintf(fp, "        add     edi, edi\n");
    fprintf(fp, "        sub     eax, edi\n");
    fprintf(fp, "        add     eax, 48\n");
    fprintf(fp, "        mov     BYTE [rsp-1+rcx], al\n");
    fprintf(fp, "        mov     eax, edx\n");
    fprintf(fp, "        mov     rdx, rcx\n");
    fprintf(fp, "        add     rcx, 1\n");
    fprintf(fp, "        test    eax, eax\n");
    fprintf(fp, "        jne     .L5\n");
    fprintf(fp, "        mov     eax, edx\n");
    fprintf(fp, ".L4:\n");
    fprintf(fp, "        imul    esi, esi, -858993459\n");
    fprintf(fp, "        lea     ecx, [rax+1]\n");
    fprintf(fp, "        movsx   rdx, ecx\n");
    fprintf(fp, "        add     esi, 429496728\n");
    fprintf(fp, "        ror     esi, 1\n");
    fprintf(fp, "        cmp     esi, 429496728\n");
    fprintf(fp, "        jbe     .L16\n");
    fprintf(fp, ".L7:\n");
    fprintf(fp, "        cdqe\n");
    fprintf(fp, "        mov     rsi, rsp\n");
    fprintf(fp, "        mov     edi, 1\n");
    fprintf(fp, "        mov     BYTE [rsp+rax], 10\n");
    fprintf(fp, "        mov     rax, 1\n");
    fprintf(fp, "        syscall\n");
    fprintf(fp, "        add     rsp, 40\n");
    fprintf(fp, "        ret\n");
    fprintf(fp, ".L16:\n");
    fprintf(fp, "        lea     edx, [rax+2]\n");
    fprintf(fp, "        movsx   rsi, eax\n");
    fprintf(fp, "        mov     eax, ecx\n");
    fprintf(fp, "        movsx   rdx, edx\n");
    fprintf(fp, ".L2:\n");
    fprintf(fp, "        mov     BYTE [rsp+rsi], 48\n");
    fprintf(fp, "        jmp     .L7\n");
    fprintf(fp, ".L8:\n");
    fprintf(fp, "        mov     edx, 2\n");
    fprintf(fp, "        mov     eax, 1\n");
    fprintf(fp, "        jmp     .L2\n");
    // dump new end

    fprintf(fp, "_start:\n");

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
            fprintf(fp, "    pop rdi\n");
            fprintf(fp, "    call dump\n");
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
