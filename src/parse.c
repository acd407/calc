#include <assert.h>
#include <ctype.h>
#include <parse.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static char *closing_pos (char *l, char *r) {
    assert (*l == '(');
    int stack_lv = 1;
    while (++l < r) {
        switch (*l) {
        case '(':
            stack_lv++;
            break;
        case ')':
            stack_lv--;
            break;
        }
        if (stack_lv == 0)
            break;
    }
    return l;
}

// 寻找表达式中第一个 level 级的运算符
static char *find (int level, char *l, char *r) {
    while (l < r) {
        if (*l == '(') {
            l = closing_pos (l, r);
        } else {
            for (int i = 0; op_priority[level][i]; i++)
                if (*l == op_priority[level][i])
                    return l;
        }
        l++;
    }
    return l;
}

#define ALLOCATE_LR_CHILDREN                                                   \
    root->l_child = malloc (sizeof (ast_t));                                   \
    assert (root->l_child);                                                    \
    root->l_child->l_child = NULL;                                             \
    root->l_child->r_child = NULL;                                             \
                                                                               \
    root->r_child = malloc (sizeof (ast_t));                                   \
    assert (root->r_child);                                                    \
    root->r_child->l_child = NULL;                                             \
    root->r_child->r_child = NULL;

// root 需预先分配好
static void DFS (ast_t *root, char *l, char *r) {
    while (l < r && isblank (*l))
        l++;
    if (l >= r) {
        root->token = NUMBER;
        root->value.number = 0;
        return;
    }

    char *pos;

    for (size_t i = 0; i < op_priority_sz; i++) {
        pos = find (i, l, r);
        if (pos != r) {
            ALLOCATE_LR_CHILDREN
            root->token = FUNCTION;

#define OPERATOR(x, y)                                                         \
    case y:                                                                    \
        root->value.operator = _##x##_;                                        \
        break;
#define FUNCTION(x, y)
            switch (*pos) {
#include <functions.lst>
            };
#undef FUNCTION
#undef OPERATOR

            DFS (root->l_child, l, pos);
            DFS (root->r_child, pos + 1, r);
            return;
        }
    }
    for (size_t i = 0; i < functions_sz; i++) {
        if (strncmp (fn_names[i], l, strlen (fn_names[i])) == 0) {
            l += strlen (fn_names[i]);
            r = closing_pos (l, r);
            l += 1;
            pos = strchr (l, ',');
            pos = pos && pos < r ? pos : r;
            ALLOCATE_LR_CHILDREN
            root->token = FUNCTION;
            root->value.operator = i;
            DFS (root->l_child, l, pos);
            DFS (root->r_child, pos + 1, r);
            return;
        }
    }
    if (*l == '(') { // 去最外层的括号
        DFS (root, l + 1, closing_pos (l, r));
    } else {
        root->token = NUMBER;
        if (l + 1 < r && tolower (*l) == 'p' && tolower (l[1]) == 'i')
            root->value.number = M_PI;
        else if (l < r && tolower (*l) == 'e')
            root->value.number = M_E;
        else
            root->value.number = l == r ? 0 : atof (l);
    }
    return;
}

ast_t *parse (char *expression) {
    ast_t *root = malloc (sizeof (ast_t));
    assert (root);
    root->l_child = NULL;
    root->r_child = NULL;
    DFS (root, expression, expression + strlen (expression));
    return root;
}
