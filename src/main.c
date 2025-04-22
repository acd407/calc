#include <assert.h>
#include <dfv.h>
#include <parse.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    char *expression = NULL;
    bool dump = false;
    if (argc == 2) {
        expression = argv[1];
    } else if (argc == 3) {
        if (0 == strcmp ("-d", argv[1]))
            expression = argv[2];
        else if (0 == strcmp ("-d", argv[2]))
            expression = argv[1];
        dump = true;
    }
    if (!expression) {
        fprintf (stderr, "usage:\n\t%s [-d] expressions\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    ast_t *root = parse (expression);

    if (dump)
        dfv_dump (root, 0);

    printf ("%g\n", dfv (root));

    dfv_free (root);
    return EXIT_SUCCESS;
}
