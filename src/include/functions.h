#pragma once

#include <stddef.h>

typedef double (*function_t) (double, double);

extern function_t functions[];
extern char *fn_names[];

#define DEFINE(x, y) _##x##_,
enum FUNCTIONS {
#include <functions.lst>
};
#undef DEFINE

extern char *op_priority[];
extern size_t op_priority_sz;
