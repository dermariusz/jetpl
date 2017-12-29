#include "jetpl.h"
#include "jetpl-lexer.h"

struct _JeTpl {
	JeTplString *view;
	JeTplToken *toks;
	size_t toks_len;
};

JeTpl *jetpl_new(JeTplString * view) {

	JeTpl * self = malloc(sizeof(JeTpl));
	self->view = view;

	JeTplLexer lexer;
    jetpl_lex_init(&lexer, view);

    size_t i;
    size_t capacity = 32;

	JeTplToken *toks = malloc(capacity*sizeof(JeTplToken));

	for (i = 0; jetpl_lex_has_next(&lexer); ++i) {
        JeTplToken *tok = toks + i;
        jetpl_lex_next(&lexer, tok);

		if (i == capacity) {
			capacity *= 2;
			self->toks = realloc(toks, capacity*sizeof(JeTplToken));
		}
	}
	self->toks = toks;
	self->toks_len = i;

	return self;
}

static void
replace_token(JeTplString *str, JeTplToken tokit[], size_t tokitlen, JeTplToken *token, JeTplString * repl) {
	size_t length = token->end - token->begin;
	jetpl_str_replace(str, token->begin, token->end, repl);
    long difflen = repl->len - length;


    size_t i;
    for (i = 0; i < tokitlen; ++i)
        jetpl_token_update_position(tokit + i, token->begin, token->end, difflen);
}

static void
replace_tokens(JeTplString *str, JeTplToken tokit[], size_t tokitlen, JeTplToken *tok1, JeTplToken *tok2, JeTplString * repl) {
    JeTplToken newtok = {tok1->begin, tok2->end, JETPL_TOK_NONE, {0}};
    replace_token(str, tokit, tokitlen, &newtok, repl);
}

static void
html_encode(JeTplString *str) {
	if (str->len == 0) return;

	size_t capacity = 2*str->len;
	size_t len = 0;
	
	char * newstr = malloc(capacity);
	char * it;
    *newstr = 0;
	
	for (it = str->data; *it; ++it) {
        if (len >= capacity) {
			capacity *= 2;
			newstr = realloc(newstr, capacity);
		}
		
		switch (*it) {
			case '&':
                strcat(newstr + len, "&amp;");
				len += 5;
				break;
			case '<':
                strcat(newstr + len, "&lt;");
				len += 4;
				break;
			case '>':
                strcat(newstr + len, "&gt;");
				len += 4;
				break;
			case '\"':
                strcat(newstr + len, "&quot;");
				len += 6;
				break;
			case '\'':
                strcat(newstr + len, "&#x2F");
				len += 5;
				break;
			default:
				(newstr + len)[0] = *it;
				(newstr + len)[1] = 0;

				len += 1;
		}
	}
	jetpl_str_free(str);
    str->capacity = capacity;
    str->data = newstr;
    str->len = len;
}

void jetpl_render(JeTpl * self, JeTplObject * obj, JeTplString *output) {
    static JeTplString nullstr;

	JeTplToken *tokit = malloc(self->toks_len*sizeof(JeTplToken));
	memcpy (tokit, self->toks, self->toks_len*sizeof(JeTplToken));

    jetpl_str_copy (output, self->view);
    
    size_t index;
    JeTplToken *begin = 0;
    
    for (index = 0; index < self->toks_len; ++index) {
    	JeTplToken *tok = tokit + index;
    	
        if (!jetpl_str_is_null(&tok->varname))
            jetpl_str_strip(&tok->varname);

    	if  ((tok->type & JETPL_TOK_VAR) == JETPL_TOK_VAR) {
    	    JeTplString rendered = {0};

			const JeTplObjectProp *prop = jetpl_obj_find_property(obj, tok->varname.data);
			
			if (prop) {
				jetpl_obj_render_property(obj, prop, NULL, 0, &rendered);

				if (tok->type != JETPL_TOK_UNESC) html_encode(&rendered);

				replace_token(output, tokit, self->toks_len, tok, &rendered);
				jetpl_str_free(&rendered);
			} else {
				// TODO: Error Handling
			}
            
    		
        } else if (tok->type == JETPL_TOK_BEGIN) {
    		begin = tok;
        } else if (tok->type == JETPL_TOK_END && begin) {
            JeTplString rendered = {0};

            char * arg = malloc(tok->begin - begin->end + 1);
    		*arg = 0;
            strncat(arg, output->data + begin->end, tok->begin - begin->end);

            const JeTplObjectProp *prop = jetpl_obj_find_property(obj, tok->varname.data);

            if (prop) {
                jetpl_obj_render_property(obj, prop, arg, tok->begin - begin->end, &rendered);

				replace_tokens(output, tokit,  self->toks_len, begin, tok, &rendered);

				jetpl_str_free(&rendered);
            } else {
            	// TODO: Error Handling
            }

            free(arg);

    	} else if (tok->type == JETPL_TOK_COMMENT) {
            replace_token(output, tokit, self->toks_len, tok, &nullstr);
    	}
    }

    free(tokit);
}

void jetpl_free(JeTpl * self) {
    JeTplToken * tokit = self->toks;

    size_t i;
    for (i = 0; i < self->toks_len ; ++i)
        jetpl_token_free(tokit + i);

    free(self->toks);
    free(self);
}
