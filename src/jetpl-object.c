#include "jetpl-object.h"

#include <assert.h>
#include <string.h>

JeTplStatus jetpl_obj_render_property (
		JeTplObject *	self,
		const char  *	property,
		bool 		inverse,
		char *		arg,
		size_t		arglen,
		JeTplString *	val)
{
	assert (self && property);
	return self->clazz->render_property_delegate(self, property, inverse, arg, arglen, val);
}
