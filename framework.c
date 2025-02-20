#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

typedef struct s_input {
    void *(*one_input)(void *input);
    void *(*two_input)(void *input1, void *input2);
    void *(*three_input)(void *input1, void *input2, void *input3);
    void *(*four_input)(void *input1, void *input2, void *input3, void *input4);
} t_input;

typedef struct s_function {
    char *name;
    union {
        void *(*function1)(void *input);
        void *(*function2)(void *input1, void *input2);
        void *(*function3)(void *input1, void *input2, void *input3);
        void *(*function4)(void *input1, void *input2, void *input3, void *input4);
    } function;
    char *description;
    int num_parameters;
    char **parameter_types;
} t_function;

typedef struct s_test {
    t_function *function1;
    t_function *function2;
    t_input *input;
    char *return_type;
    int num_tests;
} t_test;

// Function to get high precision time in nanoseconds
double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

// Function to compare outputs (supports int, double, and string)
int compare_outputs(void *result1, void *result2, char *type) {
    if (strcmp(type, "int") == 0) {
        return *(int *)result1 == *(int *)result2;
    } else if (strcmp(type, "double") == 0) {
        return *(double *)result1 == *(double *)result2;
    } else if (strcmp(type, "string") == 0) {
        return strcmp((char *)result1, (char *)result2) == 0;
    }
    return 0;
}

// Function to generate random test cases
void generate_random_test_case(void **args, char *type) {
    if (strcmp(type, "int") == 0) {
        int *rand_int = malloc(sizeof(int));
        *rand_int = rand() % 1000000;
        args[0] = rand_int;
    } else if (strcmp(type, "double") == 0) {
        double *rand_double = malloc(sizeof(double));
        *rand_double = (double)(rand() % 1000000) / 100.0;
        args[0] = rand_double;
    } else if (strcmp(type, "string") == 0) {
        char *rand_str = malloc(11);
        for (int i = 0; i < 10; i++) rand_str[i] = 'A' + (rand() % 26);
        rand_str[10] = '\0';
        args[0] = rand_str;
    }
}

// Function to benchmark and compare behavior with multiple tests
void test_functions(t_test *test) {
    int pass_count = 0;
    int func1_better = 0;
    int func2_better = 0;

    for (int i = 0; i < test->num_tests; i++) {
        void *args[1];
        generate_random_test_case(args, test->return_type);

        double start, end, time1, time2;
        void *result1;
        void *result2;

        // Measure first function
        start = get_time();
        result1 = test->function1->function.function1(args[0]);
        end = get_time();
        time1 = end - start;

        // Measure second function
        start = get_time();
        result2 = test->function2->function.function1(args[0]);
        end = get_time();
        time2 = end - start;

        // Compare outputs
        int same_output = compare_outputs(result1, result2, test->return_type);
        if (same_output) {
            pass_count++;
            if (time1 < time2) {
                func1_better++;
            } else if (time2 < time1) {
                func2_better++;
            }
        }

        free(args[0]);
        free(result1);
        free(result2);
    }

    printf("%s vs %s: %d/%d tests passed (%.2f%% correctness)\n",
           test->function1->name, test->function2->name, pass_count, test->num_tests, (pass_count / (double)test->num_tests) * 100);
    printf("%s was faster in %d cases\n", test->function1->name, func1_better);
    printf("%s was faster in %d cases\n", test->function2->name, func2_better);
}

// Example functions
void *testFunc1(void *input) {
    int *x = (int *)input;
    int *result = malloc(sizeof(int));
    *result = *x * 2;
    return result;
}

void *testFunc2(void *input) {
    int *x = (int *)input;
    int *result = malloc(sizeof(int));
    *result = (*x << 1);
    return result;
}

int main() {
    srand(time(NULL));

    t_function f1 = {"Multiply by 2", {.function1 = testFunc1}, "Multiplies input by 2", 1, (char *[]){"int"}};
    t_function f2 = {"Bitwise Shift Left", {.function1 = testFunc2}, "Shifts input left by 1 bit", 1, (char *[]){"int"}};

    t_test test = {&f1, &f2, NULL, "int", 1000000};

    test_functions(&test);

    return 0;
}
