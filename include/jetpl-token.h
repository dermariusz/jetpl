#ifndef JETPLTOKEN_H
#define JETPLTOKEN_H

#include "jetpl-string.h"

#include <stddef.h>

enum JeTplTokenType {
    JETPL_TOK_NONE = 0,
    JETPL_TOK_BEGIN,
    JETPL_TOK_END,
    JETPL_TOK_TEXT,
    JETPL_TOK_VAR,
    JETPL_TOK_UNESC = 1 << 3 | JETPL_TOK_VAR,
    JETPL_TOK_COMMENT = 1 << 3,
    JETPL_TOK_PARTIAL = 1 << 4
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
