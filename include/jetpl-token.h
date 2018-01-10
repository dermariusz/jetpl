#ifndef JETPLTOKEN_H
#define JETPLTOKEN_H

#include "jetpl-string.h"

#include <stddef.h>

enum JeTplTokenType {
    JETPL_TOK_NONE    = 0,
    JETPL_TOK_BEGIN   = 1 << 0,
    JETPL_TOK_END     = 1 << 1,
    JETPL_TOK_VAR     = 1 << 2,
    JETPL_TOK_PARTIAL = 1 << 3,
    JETPL_TOK_TEXT    = 1 << 4,
    JETPL_TOK_INVERSE = 1 << 5 | JETPL_TOK_BEGIN,
    JETPL_TOK_UNESC   = 1 << 5 | JETPL_TOK_VAR,
    JETPL_TOK_COMMENT = 1 << 5 | JETPL_TOK_TEXT
};

typedef struct _JeTplToken {
    size_t begin;
    size_t end;
    enum JeTplTokenType type;
    JeTplString varname;
} JeTplToken;

void jetpl_token_update_position(JeTplToken * self, size_t begin, size_t end, int diff);

#define jetpl_token_free(self) jetpl_str_free(&((self)->varname))

#endif // JETPLTOKEN_H
