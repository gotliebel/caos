#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    void* handle;
    double (*p_function)(double);
    char* error;
    handle = dlopen(argv[1], RTLD_LAZY);
    p_function = dlsym(handle, argv[2]);
    double value;
    while (scanf("%lf", &value) != EOF) {
        printf("%.3f\n", p_function(value));
    }
    return 0;
}