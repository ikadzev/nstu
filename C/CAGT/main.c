// Calculation and graphic task
#include <stdio.h>
#include <stdlib.h>

void floatBin(unsigned n) {
    int bins[32];
    int mask;
    for (int i = 0; i < 32; i++) {
        mask = 1 << i;
        bins[i] = (mask & n) >> i;
    }
    for (int j = 31; j >= 0; j--){
        printf("%i", bins[j]);
    }
}

void intBin(unsigned n) {
    int bins[32];
    int len = 0;
    for (int i = 0; (i < 32) && (n != 0); i++) {
        bins[len] = abs(n % 2);
        n /= 2;
        len++;
    }
    for (int j = len - 1; j >= 0; j--){
        printf("%i", bins[j]);
    }
}

int main() {
    unsigned int num_int;
    scanf("%i", &num_int);
    float num_float;
    scanf("%f", &num_float);
    intBin(num_int);
    printf("\n");
    floatBin(num_float);
    return 0;
}