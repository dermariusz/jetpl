#include "jetpl-string.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

void jetpl_str_init (JeTplString * self, const char * data, size_t len) {
	assert(self);
	
    if (data && len) {
		self->len = len;
        self->data = malloc(len + 1);
		self->capacity = len + 1;
		self->data[0] = 0;
		strncat(self->data, data, len);
	} else {
		self->len = 0;
		self->capacity = (len == 0) ? 32: len;
		self->data = malloc(self->capacity);
	}
}

void jetpl_str_init_sz (JeTplString * self, const char *sz_data) {
	jetpl_str_init(self, sz_data, strlen(sz_data));
}

void jetpl_str_init_f (JeTplString *self, const char *format, ...) {
	va_list arglist;
	va_start(arglist, format);
	int needed = vsnprintf(NULL, 0, format, arglist);
	va_end(arglist);
	if (needed > 0) {
		self->len = needed;
		self->data = malloc(needed + 1);

		va_start(arglist, format);
		vsnprintf(self->data, needed + 1, format, arglist);
		va_end(arglist);
		
		self->capacity = needed + 1;
	}
}

void jetpl_str_copy (JeTplString * dest, JeTplString * src) {
	assert(dest && src);

	dest->len = src->len;
	dest->capacity = src->capacity;

    if (dest->len > dest->capacity) {
        dest->capacity += dest->len;
    }

	dest->data = malloc(dest->capacity);
	memcpy(dest->data, src->data, src->len);
}

int jetpl_str_cmp(JeTplString * str1, JeTplString * str2) {
    size_t i;
	for (i = 0; i < str1->len && i < str2->len; ++i) {
		if (str1->data[i] != str2->data[i])
            return str1->data[i] < str2->data[i] ? -1 : 1;
    }
    return 0;
}

void jetpl_str_strip (JeTplString * self) {
    assert(self);

	size_t newbegin, newend;
	
    for (newbegin = 0; newbegin < self->len; ++newbegin)
        if (self->data[newbegin] != ' ')
			break;

    if (newbegin != 0) {
        memmove(self->data, self->data + newbegin, self->len - newbegin);
        self->len -= newbegin;
    }

    for (newend = self->len; newend > 0; --newend)
        if (self->data[newend] != ' ')
			break;

    if (newend != self->len) {
        self->len = newend + 1;
        self->data[self->len] = 0;
    }
}

void jetpl_str_replace(JeTplString * self, size_t begin, size_t end, JeTplString * str) {
    assert(begin < end && self && str);

    size_t length = end - begin;
    if (self->len - length + str->len >= self->capacity) {
        self->capacity *= 2;
        self->capacity += str->len;
    }
    
    char * concat = malloc(self->capacity);
    
    memcpy(concat, self->data, begin);
    memcpy(concat + begin, str->data, str->len);
    memcpy(concat + begin + str->len, self->data + end, self->len - end);
    concat[begin + str->len + self->len - end] = 0;

	jetpl_str_free(self);

	self->data = concat;
	self->len = begin + str->len + self->len - end;
}



