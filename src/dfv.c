#include <functions.h>
#include <parse.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

double dfv (ast_t *root) {
    if (root == NULL) {
        return 0;
    }

    if (root->token == NUMBER) {
        return root->value.number;
    } else {
        double r_child = dfv (root->r_child);
        double l_child = dfv (root->l_child);
        return functions[root->value.operator](l_child, r_child);
    }
}

void dfv_free (ast_t *root) {
    if (root && root->token == FUNCTION) {
        dfv_free (root->r_child);
        dfv_free (root->l_child);
    }
    free (root);
}

void dfv_dump (ast_t *root, int level) {
    if (level == 0) {
        puts("dump:");
    }

    if (root == NULL) {
        return;
    }

    // 先打印右子树
    dfv_dump (root->r_child, level + 1);

    // 打印当前节点
    printf("| ");
    for (int i = 0; i < level; i++) {
        printf ("    ");
    }

    switch (root->token) {
    case NUMBER:
        printf ("%g\n", root->value.number);
        break;
    case FUNCTION:
        printf ("%s\n", fn_names[root->value.operator]);
        break;
    default:
        printf ("Unknown\n");
    }

    // 最后打印左子树
    dfv_dump (root->l_child, level + 1);
}
