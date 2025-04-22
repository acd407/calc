#pragma once

#include <functions.h>
#include <stddef.h>

enum token_t { NUMBER, FUNCTION };

typedef struct _ast_t {
    enum token_t token;
    union {
        enum FUNCTIONS operator;
        double number;
    } value;
    struct _ast_t *l_child;
    struct _ast_t *r_child;
} ast_t;

ast_t *parse (char *expression);
