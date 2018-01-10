#include <stdio.h>
#include <jetpl.h>

#include "typical.h"

enum TypicalProperties {
	TYPICAL_NAME,
	TYPICAL_VALUE,
	TYPICAL_IN_CA,
	TYPICAL_TAXED_VALUE,
	TYPICAL_VERBATIM,
	TYPICAL_NONE,
	N_PROPS
};

struct _Typical {
	JeTplObject obj;
	char name[256];
	long value;
	bool in_ca;
};

const JeTplObjectProp properties[] = {
	{TYPICAL_NAME, "name"},
	{TYPICAL_VALUE, "value"},
	{TYPICAL_IN_CA, "in_ca"},
	{TYPICAL_TAXED_VALUE, "taxed_value"},
	{TYPICAL_VERBATIM, "verbatim"},
	{TYPICAL_NONE, "none"}
};

static void typical_render_property_delegate(JeTplObject *obj, int prop_id, bool inverse, char *arg, size_t arglen, JeTplString *out) {
	Typical * self = (Typical *) obj;

	switch (prop_id) {
		case TYPICAL_NAME:
			jetpl_str_init_sz (out, self->name);
			break;

		case TYPICAL_VALUE:
			jetpl_str_init_f(out, "%ld", self->value);
			break;

        case TYPICAL_IN_CA:
            if (self->in_ca) {
                JeTplString argstr = {arg, arglen, 0};
                JeTpl *tpl = jetpl_new(&argstr);
                jetpl_render(tpl, obj, out);
                jetpl_free(tpl);
            }
			break;

		case TYPICAL_TAXED_VALUE:
			jetpl_str_init_f(out, "%.0f", self->value*0.6);
			break;

		case TYPICAL_VERBATIM:
			jetpl_str_init(out, arg, arglen);
			break;

		case TYPICAL_NONE:
            if (inverse) jetpl_str_init(out, arg, arglen);
	}
}

JeTplObjectClass clazz = {typical_render_property_delegate, properties, N_PROPS};

Typical * typical_new (const char *name, long value, bool in_ca) {
	Typical *self = malloc(sizeof(Typical));
    self->obj.clazz = &clazz;
    *self->name = 0;
	strncat(self->name, name, 255);
	self->value = value;
	self->in_ca = in_ca;
	return self;
}
