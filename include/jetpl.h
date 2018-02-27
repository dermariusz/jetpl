#ifndef JETPL_H
#define JETPL_H

#include <stddef.h>

#include "jetpl-string.h"
#include "jetpl-object.h"
#include "jetpl-token.h"

typedef struct _JeTpl JeTpl;

typedef void (JeTplSimpleDel)(const char *, JeTplString *);

JeTpl * jetpl_new(JeTplString * view);

void jetpl_render(JeTpl * self, JeTplObject * obj, JeTplString * out_str);

void jetpl_free(JeTpl * self);

#endif // JETPL_H
