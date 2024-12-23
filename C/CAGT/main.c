// Calculation and graphic task
#include <stdio.h>
#include <stdlib.h>

union double_union {
    double fn;
    unsigned long long in;
};

void print_repeat(char a, int i) {
    for (int j = 0; j < i; j++) {
        printf("%c", a);
    }
}

void print_table(unsigned long long n) {
    printf("sign | characteristic | mantissa\n");
    printf("%lli", n << 1 >> 63);
    printf("      ");
    for (int i = 62; i > 51; i--) {
        printf("%lli", n << (63 - i) >> 63);
    }
    printf("      ");
    for (int i = 51; i >= 0; i--) {
        printf("%lli", n << (63 - i) >> 63);
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

void floatBin(unsigned long long n) {
    printf("binary double = \n");
    print_table(n);
    unsigned long long chara = n << 1 >> 53;
    unsigned long long mant = n << 12 >> 12;
    mant += 1 << 52;
    printf("\n%lli", chara);
    int por = chara - 1023;
    int dot = 52 - por;
    
    // int int_of_float = mant >> dot;
    // float float_of_float = 0;
    // float one = 1;
    // for (int i = dot; i > 0; i--) {
    //     one /= 2;
    //     // printf(" %f %f", one, float_of_float);
    //     if (mant << (32 - i) >> 31) {
    //         float_of_float += one;
    //     }
    // }

    // printf("\n%i", int_of_float);
    // printf(" %f", float_of_float);
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
    // unsigned int num_int;
    // printf("int: ");
    // scanf("%i", &num_int);

    union double_union num;
    printf("double: ");
    scanf("%lf", &num.fn);

    // intBin(num_int);
    // printf("\n");
    floatBin(num.in);

    return 0;
}