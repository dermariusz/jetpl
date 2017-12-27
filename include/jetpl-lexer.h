#ifndef JETPLLEXER_H
#define JETPLLEXER_H

#include "jetpl-token.h"

#include <stdbool.h>

typedef struct _JeTplLexer {
    JeTplString *view;
    size_t pos;
    JeTplString beg_var;
} JeTplLexer;

void jetpl_lex_init(JeTplLexer *self, JeTplString *view);

bool jetpl_lex_has_next(JeTplLexer * self);

void jetpl_lex_next(JeTplLexer * self, JeTplToken *tok);

#endif // JETPLLEXER_H
