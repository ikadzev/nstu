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
        printf("%c", a);
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
    printf("\n");
    // int mantissa10 = 0;
    // for (int i = 22; i >= 0; i--) {
    //     if (bins[i] == 1) {
    //         mantissa10 += 1 << i;
    //     }
    // }
    // printf("\n%i", mantissa10);
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
    int chara = (int)(n << 1 >> 24);
    unsigned int mant = (int)(n << 9 >> 9);
    mant += 1 << 23;
    int por = chara - 127;
    int dot = 23 - por;
    int int_of_float = mant >> dot;
    float float_of_float = 0;
    float one = 1;
    for (int i = dot; i > 0; i--) {
        one /= 2;
        // printf(" %f %f", one, float_of_float);
        if (mant << (32 - i) >> 31) {
            float_of_float += one;
        }
    }

    printf("\n%i", int_of_float);
    printf(" %f", float_of_float);
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