#include <functions.h>
#include <stdint.h>

static double and (double x, double y) {
    return (uint64_t) x & (uint64_t) y;
}
static double or (double x, double y) {
    return (uint64_t) x | (uint64_t) y;
}
static double xor (double x, double y) {
    return (uint64_t) x ^ (uint64_t) y;
} static double add (double x, double y) {
    return x + y;
}
static double subtract (double x, double y) {
    return x - y;
}
static double multiply (double x, double y) {
    return x * y;
}
static double divide (double x, double y) {
    return x / y;
}
static double mod (double x, double y) {
    return (uint64_t) x % (uint64_t) y;
}

#define DEFINE(x, y) x,
function_t functions[] = {
#include <functions.lst>
};
#undef DEFINE

#define DEFINE(x, y) #x,
char *fn_names[] = {
#include <functions.lst>
};
#undef DEFINE

char *op_priority[] = {
    (char[]) {'&', '|', '^', '\0'}, (char[]) {'+', '-', '\0'},
    (char[]) {'*', '/', '%', '\0'}
};
size_t op_priority_sz = sizeof (op_priority) / sizeof (char *);
