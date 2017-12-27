#ifndef JETPLOBJECT_H
#define JETPLOBJECT_H

#include <stddef.h>
#include <stdbool.h>

#include "jetpl-string.h"

typedef struct _JeTplObject JeTplObject;

typedef struct _JeTplObjectProp {
	unsigned int id;
	const char *name;
} JeTplObjectProp;

typedef struct _JeTplObjectClass {
    void (*render_property_delegate)(JeTplObject *, int, char *, size_t, JeTplString *);
    const JeTplObjectProp * properties;
    size_t prop_num;
} JeTplObjectClass;

struct _JeTplObject {
    JeTplObjectClass *clazz;
};

const JeTplObjectProp *jetpl_obj_find_property(JeTplObject * self, const char *prop_name);

void jetpl_obj_render_property(JeTplObject * self, const JeTplObjectProp *prop, char * arg, size_t arglen, JeTplString *val);

#endif // JETPLOBJECT_H
