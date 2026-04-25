
#include "src.hpp"
#include <iostream>

using namespace sjtu;

int main() {
    complex z1; // z = 0;
    complex z2 = 2.22; // z = 2.22;
    complex z3(2.22, 3.33); // z = 2.22 + 3.33i

    complex z(1, 2);
    std::cout << z.real() << "," << z.imag() << std::endl; // 输出 1,2
    z.real() = 3;
    z.imag() = 4;
    std::cout << z.real() << "," << z.imag() << std::endl; // 输出 3,4


    complex xa = 1, xb = 2, xc = 2;
    std::cout << int(xa == xb) << std::endl; // 输出 0
    std::cout << int(xb == xc) << std::endl; // 输出 1

    z += complex(1, 2);
    std::cout << z.real() << "," << z.imag() << std::endl; // 输出 4,6

    z -= complex(1.3, 2);
    std::cout << z.real() << "," << z.imag() << std::endl; // 输出 2.7,4

    z *= complex(1, 2);
    std::cout << z.real() << "," << z.imag() << std::endl; // 输出 -5.3,9.4

    z /= complex(2, 2);
    std::cout << z.real() << "," << z.imag() << std::endl; // 输出 1.025,3.675

    try {
        z /= complex(0, 0);
    } catch(const std::exception &err) {
        // 此处应该输出(不包含引号) "complex divided by zero!"
        std::cout << err.what() << '\n'; 
    }

    complex a(-2,0);
    complex b(0,-2);
    complex c(1,-1e-10);
    complex d(-1e-10,1);
    std::cout << a << std::endl; // 输出 -2.000000+0.000000i
    std::cout << b << std::endl; // 输出 0.000000-2.000000i
    std::cout << c << std::endl; // 输出 1.000000+0.000000i  用加号，因为它的虚部绝对值在 10^-6 以内，认为是 0。 属于非负数
    std::cout << d << std::endl; // 输出 0.000000+1.000000i  实部无符号，因为它的绝对值在 10^-6 以内，认为是 0。 属于非负数


    if (a) {
        std::cout << "a is not zero!" << std::endl; // a is not zero!
    } else {
        std::cout << "a is zero!" << std::endl;
    }
    
}
