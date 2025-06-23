#include <functions.h>
#include <stdint.h>
#include <math.h>

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
static double sine (double x, double y) {
    return sin(x + y);
}
static double cosine (double x, double y) {
    return cos(x + y);
}
static double tangent (double x, double y) {
    return tan(x + y);
}
static double exponential (double x, double y) {
    return exp(x + y);
}
static double power(double x, double y) {
    return pow(x, y);
}
static double logarithm(double x, double y) {
    return log(y) / log(x);
}

#define OPERATOR(x, y) x,
#define FUNCTION(x, y) x,
function_t functions[] = {
#include <functions.lst>
};
#undef FUNCTION
#undef OPERATOR

#define OPERATOR(x, y) #x,
#define FUNCTION(x, y) #y,
char *fn_names[] = {
#include <functions.lst>
};
#undef FUNCTION
#undef OPERATOR
size_t functions_sz = sizeof (functions) / sizeof (function_t);

char *op_priority[] = {
    (char[]) {'&', '|', '^', '\0'}, (char[]) {'+', '-', '\0'},
    (char[]) {'*', '/', '%', '\0'}
};
size_t op_priority_sz = sizeof (op_priority) / sizeof (char *);
