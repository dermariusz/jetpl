#include <jetpl-string.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int ret = 0;

	JeTplString str;
	JeTplString expected;

	jetpl_str_init_sz(&str, " Hello ");
	jetpl_str_init_sz(&expected, "Hello");

	jetpl_str_strip(&str);

	if (jetpl_str_cmp(&str, &expected) != 0) {
		printf("Expected: %s, Got: %s", expected.data, str.data);
		ret = 1;
	}
	jetpl_str_free(&str);
	jetpl_str_free(&expected);

	return ret;
}
