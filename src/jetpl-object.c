#include "jetpl-object.h"

#include <assert.h>
#include <string.h>

const JeTplObjectProp *jetpl_obj_find_property(JeTplObject * self, const char *prop_name) {
	size_t i;
    for (i = 0; i < self->clazz->prop_num; ++i)
		if (strcmp(prop_name, self->clazz->properties[i].name) == 0)
			return self->clazz->properties + i;

	return NULL;
}

void jetpl_obj_render_property(JeTplObject * self, const JeTplObjectProp *prop, char * arg, size_t arglen, JeTplString *val) {
	assert (self && self->clazz && self->clazz->render_property_delegate && prop);
	self->clazz->render_property_delegate(self, prop->id, arg, arglen, val);
}
