#ifndef JETPL_H
#define JETPL_H

#include <stddef.h>

#include "jetpl-string.h"
#include "jetpl-object.h"
#include "jetpl-token.h"

typedef struct _JeTpl JeTpl;

typedef void (JeTplSimpleDel)(const char *, JeTplString *);

/* Some wise guy on the internet told one day that global variables are evil.
 * However, these variablea are only meant to be changed during application initializiation,
 * so in that particular case it should be okay for the variables to be global.
 */
extern JeTplSimpleDel * jetpl_render_partial_delegate;
extern JeTplSimpleDel * jetpl_render_property_not_found_delegate;

JeTpl * jetpl_new(JeTplString * view);

void jetpl_render(JeTpl * self, JeTplObject * obj, JeTplString * out_str);

void jetpl_free(JeTpl * self);

#endif // JETPL_H
