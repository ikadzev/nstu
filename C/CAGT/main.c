#include <stdio.h>
#include <stdint.h>

union struc { double d; uint64_t u; };

uint64_t sign(uint64_t n) { return n >> 63; }

uint64_t chara(uint64_t n) { return (n << 1 >> 53); }

uint64_t mant(uint64_t n) { 
    uint64_t o = n << 12 >> 12;
    o = o | 0x10000000000000;
    return o;
}

void print_bin(uint64_t n) { for(size_t i = 0; i < 64; i++) { printf("%li", n << i >> 63); } }

void print_table(uint64_t n) {
    printf("sign | characteristic | mantissa\n");
    printf("----------------------------------------------------------------------------\n");
    printf("%li    | ", n >> 63);
    for (size_t i = 1; i < 12; i++) { printf("%li", n << i >> 63); }
    printf("    | ");
    for (size_t i = 12; i < 64; i++) { printf("%li", n << i >> 63); }
    return;
}

void print_intbin(uint64_t n) {
    uint64_t mant_temp = mant(n);
    int64_t order = chara(n) - 1023;
    if (order >= 0) {
        for (size_t i = 0; i < order + 1; i++) {
            printf("%li", mant_temp << 11 + i >> 63);
        }
    }
    else {
        printf("0");
    }
    return;
}

void print_doublebin(uint64_t n) {
    uint64_t mant_temp = mant(n);
    uint64_t order = chara(n) - 1023;
    for (size_t i = 0; i < 52 - order; i++) {
        printf("%li", mant_temp << 12 + order + i >> 63);
    }
    return;
}

void print_intint(uint64_t n) {
    if (sign(n)) { printf("-"); }
    uint64_t mant_temp = mant(n);
    uint64_t order = chara(n) - 1023;
    uint64_t num = mant_temp >> (52 - order);
    printf("%lu", num);
    return;
}

void print_doubleint(uint64_t n) {
    uint64_t order = chara(n) - 1023;
    uint64_t frac = mant(n) << (12 + order) >> (12 + order);
    uint64_t one = 0xFFFFFFFFFFFFFFFF;
    uint64_t compare = one << 52 - order;
    uint64_t reset = one >> 12 + order;
    while (frac > 0) {
        frac *= 10;
        printf("%li", (frac & compare) >> 52 - order);
        frac = frac & reset;
    }
    return;
}

int main() {
    union struc num;
    printf("double: ");
    scanf("%lf", &num.d);

    printf("binary double: ");
    print_bin(num.u);
    printf("\n");
    print_table(num.u);
    printf("\n\n | Order: %li  Corrected order: %li", chara(num.u), chara(num.u) - 1023);

    printf("\n || Integer part in binary: ");
    print_intbin(num.u);
    printf("\n || Fractional part in binary: 0.");
    print_doublebin(num.u);
    
    printf("\n ||| Number from binary double: ");
    print_intint(num.u);
    printf(".");
    print_doubleint(num.u);
    printf("\n");
    return 0;
}