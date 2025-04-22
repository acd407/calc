#pragma once

#include <parse.h>

double dfv (ast_t *root);
void dfv_dump (ast_t *root, int level);
void dfv_free (ast_t *root);
