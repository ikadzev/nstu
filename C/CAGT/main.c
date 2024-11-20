// Calculation and graphic task
#include <stdio.h>
#include <stdlib.h>

union float_union {
    float fn;
    unsigned un;
    int in;
};

void print_repeat(char a, int i) {
    for (int j = 0; j < i; j++) {
        printf(&a);
    }
}

void print_table(int* bins) {
    printf("sign | characteristic | mantissa\n");
    printf("%i", bins[31]);
    printf("      ");
    for (int i = 30; i > 22; i--) {
        printf("%i", bins[i]);
    }
    printf("         ");
    for (int i = 22; i >= 0; i--) {
        printf("%i", bins[i]);
    }
}

void floatBin(unsigned n) {
    int bins[32];
    int mask;
    for (int i = 0; i < 32; i++) {
        mask = 1 << i;
        bins[i] = (mask & n) >> i;
    }
    printf("binary float = \n");
    print_table(bins);
}

void intBin(unsigned n) {
    int bins[32];
    int len = 0;
    for (int i = 0; (i < 32) && (n != 0); i++) {
        bins[len] = abs(n % 2);
        n /= 2;
        len++;
    }
    printf("binary int = ");
    for (int j = len - 1; j >= 0; j--){
        printf("%i", bins[j]);
    }
}

int main() {
    unsigned int num_int;
    printf("int: ");
    scanf("%i", &num_int);

    union float_union num;
    printf("float: ");
    scanf("%f", &num.fn);

    intBin(num_int);
    printf("\n");
    floatBin(num.un);

    return 0;
}