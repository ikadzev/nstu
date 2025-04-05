#include <iostream>
#include <vector>

bool isSimple(int num, int &iterations) {
    for (int i = 2; i <= num / 2; ++i) {
        ++iterations;
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int numToSimples(int inp) {
    int itr = 0;
    for (int i = 1; i < inp / 2; ++i) {
        bool simp = isSimple(i, itr);
        if (simp) {
            simp = isSimple(inp - i, itr);
            if (simp) {
                return itr;
            }
        }
    }
    return itr;
}

int main() {
    std::vector<int> tests = {8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
    std::cout << "num     | Te1    | T1     | Te1/T1 " << std::endl;
    std::cout << std::string(35, '-') << std::endl;
    
    for (int i : tests) {
        std::cout << i << "\t| ";
        int test = numToSimples(i);
        std::cout << test << "\t| ";
        std::cout << (i / 2) << "\t| ";
        std::cout << (static_cast<double>(test) / (i / 2)) << std::endl;
    }
    return 0;
}
