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

struct JeTplProperty {
	const char *		name;
	enum TypicalProperties	id;
};

const struct JeTplProperty properties[] = {
	{"name",	TYPICAL_NAME},
	{"value",	TYPICAL_VALUE},
	{"in_ca",	TYPICAL_IN_CA},
	{"taxed_value",	TYPICAL_TAXED_VALUE},
	{"verbatim",	TYPICAL_VERBATIM},
	{"none",	TYPICAL_NONE}
};

static JeTplStatus typical_render_property_delegate (
    JeTplObject *	obj,
    const char *	property,
    bool		inverse,
    char *		arg,
    size_t		arglen,
    JeTplString *	out)
{

	Typical * self = (Typical *) obj;
	size_t i;
	size_t prop_id;

	for (i = 0; i < N_PROPS; ++i)
		if (strcmp(property, properties[i].name) == 0)
			goto found_marker;

	return JETPL_STATUS_PROP_NOT_FOUND;

found_marker:
	prop_id = properties[i].id;

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
	return JETPL_STATUS_OK;
}

JeTplObjectClass clazz = {typical_render_property_delegate};

Typical * typical_new (const char *name, long value, bool in_ca) {
	Typical *self = malloc(sizeof(Typical));
	self->obj.clazz = &clazz;
	*self->name = 0;
	strncat(self->name, name, 255);
	self->value = value;
	self->in_ca = in_ca;
	return self;
}
