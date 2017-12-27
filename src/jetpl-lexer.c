#include "jetpl-lexer.h"

static const JeTplString nullstr;

void jetpl_lex_init(JeTplLexer *self, JeTplString *view) {
    self->view = view;
	self->pos = 0;
	self->beg_var = nullstr;
}

bool jetpl_lex_has_next(JeTplLexer *self) {
	return self->pos < self->view->len;
}

void jetpl_lex_next(JeTplLexer *self, JeTplToken *tok) {

    size_t begin, end;

    begin = self->pos;
    end   = self->pos;

    if (self->view->data[end] == '{' && end + 1 < self->view->len && self->view->data[end + 1] == '{') {

        end += 2;

        if (jetpl_str_is_null(&self->beg_var) || self->view->data[end] == '/') {
        	enum JeTplTokenType type;

            switch (self->view->data[end]) {
            case '#':
                type = JETPL_TOK_BEGIN;
                end++;
                break;

            case '/':
                type = JETPL_TOK_END;
                self->beg_var = nullstr;
                end++;
                break;

            case '{':
                type = JETPL_TOK_UNESC;
                end++;
                break;

            case '!':
                type = JETPL_TOK_COMMENT;
                end++;
                break;

            default:
                type = JETPL_TOK_VAR;
                break;
            }

			JeTplString varname;

            size_t eot, i;
            for (i = end; i < self->view->len; ++i) {
                if (type == JETPL_TOK_UNESC && strncmp("}}}", self->view->data + i, 3) == 0) {
                    jetpl_str_init(&varname, self->view->data + end, i - end);
                    eot = i;
                    eot += 3;
                    break;
                }
                else if (type != JETPL_TOK_UNESC && strncmp("}}", self->view->data + i, 2) == 0) {
                    jetpl_str_init(&varname, self->view->data + end, i - end);
                    eot = i;
                    eot += 2;
                    break;
                }
            }
            if (type == JETPL_TOK_BEGIN)
            	self->beg_var = varname;

            self->pos = eot;
            
            tok->begin = begin;
            tok->end   = eot;
            tok->type  = type;
            tok->varname = varname;

        } else {
            end++;
            self->pos = end;

			tok->begin = begin;
			tok->end = end;
			tok->type = JETPL_TOK_TEXT;
			tok->varname = nullstr;
        }
        return;
    }

    while (end < self->view->len) {
        if (end != 0 && self->view->data[end - 1] == '{' && self->view->data[end] == '{') {
            end -= 2;
            break;
        }
        end++;
    }
    end++;
    self->pos = end;
    
    tok->begin = begin;
    tok->end = end;
    tok->type = JETPL_TOK_TEXT;
    tok->varname = nullstr;
}
