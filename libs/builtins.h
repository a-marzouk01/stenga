#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdio.h>

void prologue(FILE *fp);
void dump_code(FILE *fp);
void push_code(FILE *fp, int x);
void plus_code(FILE *fp);
void sub_code(FILE *fp);
void print_code(FILE *fp);
void epilogue(FILE *fp);

#endif /* BUILTINS_H */
