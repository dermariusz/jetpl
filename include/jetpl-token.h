#ifndef JETPLTOKEN_H
#define JETPLTOKEN_H

#include "jetpl-string.h"

#include <stddef.h>

enum JeTplTokenType {
    JETPL_TOK_NONE,
    JETPL_TOK_BEGIN,
    JETPL_TOK_END,
    JETPL_TOK_VAR,
    JETPL_TOK_UNESC = 7,
    JETPL_TOK_TEXT = 8,
    JETPL_TOK_COMMENT = 16
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
