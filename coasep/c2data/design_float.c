#include <stdio.h>

union {
    int i;
    float f;
} myunion;

int binstr2int(char *s)
{
    int rc;
    for (rc = 0; '\0' != *s; s++) {
        if ('1' == *s) {
            rc = (rc * 2) + 1;
        } else if ('0' == *s) {
            rc *= 2;
        }
    }
    return rc;
}

int main(void) {

    // the input binary string (4 bytes)
    char * input = "11000000110110011001100110011010";
    float *output;


    // convert to int, sizeof(int) == sizeof(float) == 4
    int converted = binstr2int(input);

    // strat 1: point memory of float at the int
    output = (float*)&converted; // cast to suppress warning
    printf("%f\n", *output); // -6.8

    // strat 2: use a union to share memory
    myunion.i = converted;
    printf("%f\n", myunion.f); // -6.8

    return 0;
}
