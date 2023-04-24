#include <iostream>

using namespace std;
const uint32_t N = 5;

int main()
{
    uint32_t* M = new uint32_t[N]();
    for (uint32_t i = 0; i < N; ++i) {
        M[i] = 0x44332211;
    }
    size_t k = 3;
    asm(
    "movl $68, (%[M], %[k], 4)\n"
    :
    : [M] "r" (M), [k] "r" (k)
    :"cc"
    );

    std::cout << std::hex;
    for (uint32_t i = 0; i < N; ++i) {
        std::cout << M[i] << ' ';
    }
    std::cout << endl;

    size_t j = 1;
    asm(
    "movb $0xFF, 3(%[M], %[j], 4)\n"
    :
    : [M] "r" (M), [j] "r" (j)
    : "cc"
    );

    for (uint32_t i = 0; i < N; ++i) {
        std::cout << M[i] << ' ';
    }
    cout << endl;
    delete[] M;

    int x = 10;
    int y = 12;
    int z = 0, w = 0;
    asm(
    "add $-7, %[Y]\n"
    "mov $0, %%edx\n"
    "div %[Y]\n"
    : [Z] "=a" (z), [W] "=&d" (w)
    : [X] "a" (x), [Y] "r" (y)
    : "cc"
    );
    cout << "z = " << z << endl;
    cout << "w = " << w << endl;

    x = 10;
    y = 12;
    z = 0;
    w = 0;
    asm(
    "movl %[X], %%eax\n"
    "movl %[Y], %%ecx\n"
    "add $-7, %%ecx\n"
    "mov $0, %%edx\n"
    "div %%ecx\n"
    : [Z] "=a" (z), [W] "=&d" (w)
    : [X] "m" (x), [Y] "m" (y)
    : "cc", "ecx"
    );
    cout << "z = " << z << endl;
    cout << "w = " << w << endl;
}
