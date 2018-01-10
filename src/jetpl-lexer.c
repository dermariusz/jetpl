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

    if (strncmp(self->view->data + end, "{{", 2) == 0) {

        end += 2;

        if (jetpl_str_is_null(&self->beg_var) || self->view->data[end] == '/') {
        	enum JeTplTokenType type = JETPL_TOK_NONE;

            switch (self->view->data[end]) {
            	case '#': if (!type) type = JETPL_TOK_BEGIN;
            	case '^': if (!type) type = JETPL_TOK_INVERSE;
       			case '/': if (!type) type = JETPL_TOK_END;
            	case '&':
            	case '{': if (!type) type = JETPL_TOK_UNESC;
            	case '!': if (!type) type = JETPL_TOK_COMMENT;
            		end++;
            		break;
                default:
                	type = JETPL_TOK_VAR;
            }

        	JeTplString varname = {0};
			size_t eot;

            for (eot = end; eot < self->view->len; ++eot) {
                if (type == JETPL_TOK_UNESC && strncmp("}}}", self->view->data + eot, 3) == 0) {
                    jetpl_str_init(&varname, self->view->data + end, eot - end);
                    eot += 3;
                    break;
                }
                else if (strncmp("}}", self->view->data + eot, 2) == 0) {
                    jetpl_str_init(&varname, self->view->data + end, eot - end);
                    eot += 2;
                    break;
                }
            }

			if (type == JETPL_TOK_END) {
				if (jetpl_str_cmp(&self->beg_var, &varname) != 0)
					// This current token is wrongly detected as JETPL_TOK_END because the variable name
					// of the JETPL_TOK_BEGIN token and the name of the curent token are different.
					// This is needed in order to support to nested sections.
					goto treat_current_token_as_text;

    			self->beg_var = nullstr; // Reset
			} else if (type & JETPL_TOK_BEGIN) {
            	self->beg_var = varname; // Set
            }

            self->pos = eot;
            
            tok->begin = begin;
            tok->end   = eot;
            tok->type  = type;
            tok->varname = varname;
            return;
        }
    }

treat_current_token_as_text:
    while (end < self->view->len) {
        if (strncmp(self->view->data + end, "{{", 2) == 0)
        	break;
        end++;
    }
    self->pos = end;
    
    tok->begin = begin;
    tok->end = end;
    tok->type = JETPL_TOK_TEXT;
    tok->varname = nullstr;
}
