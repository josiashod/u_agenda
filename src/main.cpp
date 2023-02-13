#include <iostream>
#include <cstring>
#include "main.h"

void test1()
{
    std::cout << "Everything is okay";
    exit (OK);
}

int main(int argc, char **argv)
{
    unsigned int i = 0;
	test_t tests[] = {
		{"test1", test1},
		{"", NULL}
	};

    if (argc > 1)
    {
        while (tests[i].func != NULL && strcmp(tests[i].test.c_str(), argv[1]))
            i++;

        if (tests[i].test != "")
            tests[i].func();
    }

    exit(0);
}