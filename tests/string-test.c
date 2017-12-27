#include <jetpl-string.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int ret = 0;

    const char expected_rslt[] = "01abcde4";

	JeTplString str1;
	JeTplString repl;

	jetpl_str_init_sz(&str1, "01234");
	jetpl_str_init_sz(&repl, "abcde");
	
	jetpl_str_replace(&str1, 2, 4, &repl);
	
	JeTplString copy;
	
	jetpl_str_copy(&copy, &str1);

	jetpl_str_free(&str1);

	if (strcmp(copy.data, expected_rslt) != 0 ) {
		printf("Expected: %s, Got: %s", expected_rslt, copy.data);
		ret = 1;
	}

	jetpl_str_free(&copy);
	jetpl_str_free(&repl);
	return ret;
}
