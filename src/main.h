#ifndef __MAIN__
#define __MAIN__

// Error 
enum error {
    OK                         = 0, // Everything is ok
    ERR_NOT_FOUND              = 1, // Resource not found
};

/**
 * struct test - Struct of an option 
 * @test: the test
 * @func: the function associated to this option
 */
typedef struct test {
    std::string test;
    void (*func)();
} test_t;

#endif