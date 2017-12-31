#ifndef JETPL_H
#define JETPL_H

#include <stddef.h>

#include "jetpl-string.h"
#include "jetpl-object.h"
#include "jetpl-token.h"

typedef struct _JeTpl JeTpl;

typedef void (JETPL_RPNFD)(const char *, JeTplString *);

/* Some wise guy on the internet told one day that global variables are evil.
 * However, this variable is only meant to be changed during application initializiation,
 * so in that particular case it should be okay for the variable to be global.
 */
extern JETPL_RPNFD *jetpl_render_property_not_found_delegate;

JeTpl *jetpl_new(JeTplString * view);

void jetpl_render(JeTpl * self, JeTplObject * obj, JeTplString * out_str);

void jetpl_free(JeTpl * self);

#endif // JETPL_H
