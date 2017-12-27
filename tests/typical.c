#include <stdio.h>
#include <jetpl.h>

#include "typical.h"

enum TypicalProperties {
	TYPICAL_NAME,
	TYPICAL_VALUE,
	TYPICAL_IN_CA,
	TYPICAL_TAXED_VALUE,
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
	{TYPICAL_TAXED_VALUE, "taxed_value"}
};

static void typical_render_property_delegate(JeTplObject *obj, int prop_id, char *arg, size_t arglen, JeTplString *out) {
	Typical * self = (Typical *) obj;
	switch (prop_id) {
		case TYPICAL_NAME:
			jetpl_str_init_sz (out, self->name);
			break;

		case TYPICAL_VALUE:
            out->data = malloc(64);
            out->capacity = 64;
            snprintf(out->data, 63, "%ld", self->value);
			out->len = strlen(out->data);
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
            out->data = malloc(64);
            out->capacity = 64;
            snprintf(out->data, 63, "%.0f", self->value*0.6);
			out->len = strlen(out->data);
			break;
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
