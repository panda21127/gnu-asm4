#include <iostream>

using namespace std;
const uint32_t N = 5;



int main()
{
    cout << " 1" << endl;
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

    cout << " 2" << endl;
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

    cout << " 3" << endl;
    int x = 10;
    int y = 12;
    int z = 0, w = 0;
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

    cout << " 4" << endl;
    x = 10;
    y = 12;
    z = 0;
    w = 0;
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

    cout << " 5" << endl;
    x = 10;
    y = 12;
    z = 0, w = 0;
    int* p=&x;
    int* q=&y;
    asm(
    "add $-7, %[pY]\n"
    "mov $0, %%edx\n"
    "div %[pY]\n"
    : [Z] "=a" (z), [W] "=&d" (w)
    : [pX] "a" (*p), [pY] "r" (*q)
    : "cc"
    );
    cout << "z = " << z << endl;
    cout << "w = " << w << endl;

    cout << " 6" << endl;
    short x1 = 10;
    short y1 = 12;
    short z1 = 0, w1 = 0;
    asm(
    "mov %[X], %%ax\n"
    "mov %[Y], %%cx\n"
    "add $-7, %%cx\n"
    "mov $0, %%dx\n"
    "div %%cx\n"
    : [Z] "=a" (z1), [W] "=&d" (w1)
    : [X] "m" (x1), [Y] "m" (y1)
    : "cc", "cx"
    );
    cout << "z = " << z1 << endl;
    cout << "w = " << w1 << endl;

    cout << " 7" << endl;
    x=90, y=900, z=0, w = 0;
    asm(
        "mov %[X], %%eax\n"
        "mov %[Y], %%ecx\n"
        "addl %%ecx, %%eax\n"
        "seto %%cl\n"
        "movzbl %%cl, %%ecx\n"
        "mov %%ecx, %[W]\n"
      :[Z]"=a"(z), [W]"=m"(w)
      :[X]"m"(x), [Y]"m"(y)
      :"cc", "ecx"
    );
    cout << dec;
    cout << "z = " << z << endl;
    cout << "w = " << w << endl;

    cout << " 8" << endl;
    x= 1;
    asm(
        "mov %[X], %%eax\n"
        "cmp $1, %%eax\n"
        "setc %%cl\n"
        "movzbl %%cl, %%ecx\n"
        "mov %%ecx, %[W]\n"
        :[Z]"=a"(z), [W]"=m"(w)
        :[X]"m"(x)
        :"cc", "ecx"
    );
    cout << "z = " << z << endl;
    cout << "w = " << w << endl;

    cout << " 9" << endl;
    x= 1;
    asm(
        "mov %[X], %%eax\n"
        "cmp $1, %%eax\n"
        "setl %%cl\n"
        "movzbl %%cl, %%ecx\n"
        "mov %%ecx, %[W]\n"
        :[Z]"=a"(z), [W]"=m"(w)
        :[X]"m"(x)
        :"cc", "ecx"
    );
    cout << "z = " << z << endl;
    cout << "w = " << w << endl;

    cout << " 10" << endl;
    double a = 1.00;
    double x2 = 0.08;
    bool p1, p2;

    asm("vmovsd %[A], %%xmm0\n"
        "vmovsd %[X], %%xmm1\n"
        "vcomisd %%xmm0, %%xmm1\n"
        "setc %[P1]\n"
        "setnz %[P2]\n"
    :[P1]"=r"(p1),[P2]"=r"(p2)
    :[A] "m" (a), [X] "m" (x2)
    :"cc"
    );
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;

    cout << " 11" << endl;
    a = 1.00, x2 = -1;
    asm("vmovsd %[A], %%xmm0\n"
        "vmovsd %[X], %%xmm1\n"
        "cmpltsd %%xmm0, %%xmm1\n"
        "vmovmskpd %%xmm1, %%eax\n"      //помещает младшие биты xmm1 в младшие биты регистра eax
        "and $1, %%eax\n"              
        "movzbl %%al, %[Z]\n"
    :[Z] "=r" (z)
    :[A] "m" (a), [X] "m" (x)
    :"cc", "eax"
    );
    cout << "z = " << z << endl;

    cout << " 12" << endl;
    double x10 = 1.2;
    z = 0;
    asm("fld1\n"                 
        "fldl %[X]\n" 
        "fucomip %%st(1),%%st(0)\n"
        "setc %%cl\n"
        "movzbl %%cl, %%ecx\n"
        "mov %%ecx, %[Z]\n"
    :[Z]"=m"(z)
    :[X]"m"(x10)
    :"cc", "ecx"
    );
    cout << "z = " << z << endl;

    cout << " 13" << endl;
    float x12 = 1.26;
    z = 0;
    asm("fld1\n"
        "flds %[X]\n" 
        "fucomip %%st(1),%%st(0)\n"
        "setc %%cl\n"
        "movzbl %%cl, %%ecx\n"
        "mov %%ecx, %[Z]\n"
    :[Z]"=m"(z)
    :[X]"m"(x12)
    :"cc", "ecx"
    );
    cout << "z = " << z << endl;

    cout << " 14" << endl;
    long double x9 = -15678.2345;
    z = 0;
    asm("fld1\n"
        "fldt %[X]\n"               
        "fucomip %%st(1),%%st(0)\n"
        "setc %%cl\n"
        "movzbl %%cl, %%ecx\n"
        "mov %%ecx, %[Z]\n"
    :[Z]"=m"(z)
    :[X]"m"(x9)
    :"cc", "ecx"
    );
    cout << "z = " << z << endl;
    return 0;
}
