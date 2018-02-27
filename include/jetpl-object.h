#ifndef JETPLOBJECT_H
#define JETPLOBJECT_H

#include <stddef.h>
#include <stdbool.h>

#include "jetpl-status.h"
#include "jetpl-string.h"

typedef struct _JeTplObject JeTplObject;

typedef JeTplStatus (JeTplExtendedDel)(JeTplObject *, const char *, bool, char *, size_t, JeTplString *); 

typedef struct _JeTplObjectClass {
    JeTplExtendedDel * render_property_delegate;
} JeTplObjectClass;

struct _JeTplObject {
    JeTplObjectClass * clazz;
};

JeTplStatus jetpl_obj_render_property (
		JeTplObject *	self,
		const char  *	property,
		bool		inverse,
		char *		arg,
		size_t		arglen,
		JeTplString *	val);

#endif // JETPLOBJECT_H
