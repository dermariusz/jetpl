#ifndef JETPLSTRING_H
#define JETPLSTRING_H

#include <stddef.h>
#include <stdlib.h>

typedef struct _JeTplString {
    char *data;
    size_t len;
    size_t capacity;
} JeTplString;

void jetpl_str_init(JeTplString * self, const char *data, size_t len);

void jetpl_str_init_sz(JeTplString *self, const char *sz_data);

void jetpl_str_copy(JeTplString * destination, JeTplString * source);

int jetpl_str_cmp(JeTplString * str1, JeTplString * str2); 

#define jetpl_str_is_null(self) (self)->len == 0

void jetpl_str_strip(JeTplString * self);

void jetpl_str_replace(JeTplString * self, size_t begin, size_t end, JeTplString * str);

#define jetpl_str_free(self) free((self)->data)

#endif // JETPLSTRING_H 
