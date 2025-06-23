#pragma once

#include <stddef.h>

typedef double (*function_t) (double, double);

extern function_t functions[];
extern char *fn_names[];

#define OPERATOR(x, y) _##x##_,
#define FUNCTION(x, y) _##x##_,
enum FUNCTIONS { // idx for functions and fn_names
#include <functions.lst>
};
#undef FUNCTION
#undef OPERATOR

extern size_t functions_sz;

extern char *op_priority[];
extern size_t op_priority_sz;
