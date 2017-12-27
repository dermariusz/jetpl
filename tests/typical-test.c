#include <stdio.h>
#include <jetpl.h>

#include "typical.h"

int main () {
    int ret = 0;
    JeTplString expected;
    JeTplString output;
    JeTplString view;

    jetpl_str_init_sz(&expected, "Hello Chris\n"
                                 "You have just won 10000 dollars!\n"
                                 "Well, 6000 dollars, after taxes.\n");

    jetpl_str_init_sz(&view, "Hello {{ name }}\n"
                             "You have just won {{value}} dollars!\n"
                             "{{#in_ca}}Well, {{taxed_value}} dollars, after taxes.\n{{/in_ca}}");

	JeTpl *tpl = jetpl_new(&view);
    JeTplObject *obj =  (JeTplObject *) typical_new("Chris", 10000, true);
	
	
	jetpl_render(tpl, obj, &output);
	
    if (jetpl_str_cmp(&output, &expected) != 0) {
        printf("Expected: %s, Got: %s", expected.data, output.data);
        ret = 1;
    }

    jetpl_str_free(&expected);
	jetpl_str_free(&output);
    jetpl_str_free(&view);

    free(obj);

    jetpl_free(tpl);
    return ret;
}
