#include "builtins.h"
#include <stdio.h>

void prologue(FILE *fp) {
    fprintf(fp, "section .text\n");
    fprintf(fp, "global _start\n");
}

void dump_code(FILE *fp) {
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
}

void push_code(FILE* fp, int x) {
    fprintf(fp, "    ;; push %d\n", x);
    fprintf(fp, "    push %d\n", x);
}

void plus_code(FILE *fp) {
    fprintf(fp, "    ;; add\n");
    fprintf(fp, "    pop rax\n");
    fprintf(fp, "    pop rbx\n");
    fprintf(fp, "    add rax, rbx\n");
    fprintf(fp, "    push rax\n");
}

void sub_code(FILE *fp) {
    fprintf(fp, "    ;; sub\n");
    fprintf(fp, "    pop rax\n");
    fprintf(fp, "    pop rbx\n");
    fprintf(fp, "    sub rax, rbx\n");
    fprintf(fp, "    push rax\n");
}

void print_code(FILE *fp) {
    fprintf(fp, "    ;; print\n");
    fprintf(fp, "    pop rdi\n");
    fprintf(fp, "    call dump\n");
}

void epilogue(FILE *fp) {
    fprintf(fp, "\n");
    fprintf(fp, "    mov rax, 60\n");
    fprintf(fp, "    mov rdi, 0\n");
    fprintf(fp, "    syscall\n");
}
