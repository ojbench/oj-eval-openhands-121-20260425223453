
#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <iostream> // 输入输出
#include <iomanip>  // 控制输出格式
#include <cmath>    // 数学函数
#include <stdexcept> // 异常处理
// 你不可以使用任何其他的头文件!

namespace sjtu {

// 异常类，你需要要添加一个函数 what() 来返回异常信息。
class divided_by_zero final : public std::exception {
  public:
    divided_by_zero()   = default;
    ~divided_by_zero()  = default;
    
    const char* what() const noexcept override {
        return "complex divided by zero!";
    }
};

// 用于判断浮点数的符号.
inline int sign(double x) {
    const double eps = 1e-6;
    return (x > eps) - (x < -eps);
}

// 请保留所有的接口声明，即使你没有实现它们。
// 否则可能出现编译错误，无法通过部分测试点。
// TODO 补全类的实现
class complex {
  private:
    double a, b; // a + bi
  public:
    
    complex() : a(0), b(0) {}                    // 默认构造函数 0+0i
    complex(double a_val) : a(a_val), b(0) {}            // 构造函数 a+0i
    complex(double a_val, double b_val) : a(a_val), b(b_val) {}  // 构造函数 a+bi

    double &real() { return a; } // 返回实部
    double &imag() { return b; } // 返回虚部

    complex operator - () const { // 返回负数
        return complex(-a, -b);
    }
    
    complex operator ~ () const { // 返回共轭复数
        return complex(a, -b);
    }

    complex operator + (const complex &rhs) const { // 加法
        return complex(a + rhs.a, b + rhs.b);
    }
    
    complex operator - (const complex &rhs) const { // 减法
        return complex(a - rhs.a, b - rhs.b);
    }
    
    complex operator * (const complex &rhs) const { // 乘法
        // (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
        return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
    }
    
    complex operator / (const complex &rhs) const { // 除法
        // (a + bi) / (c + di) = (a + bi)(c - di) / (c^2 + d^2)
        // = (ac + bd) / (c^2 + d^2) + (bc - ad) / (c^2 + d^2)i
        double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
        
        // Check for division by zero (within epsilon)
        if (std::abs(rhs.a) < 1e-6 && std::abs(rhs.b) < 1e-6) {
            throw divided_by_zero();
        }
        
        return complex(
            (a * rhs.a + b * rhs.b) / denominator,
            (b * rhs.a - a * rhs.b) / denominator
        );
    }

    complex &operator += (const complex &rhs) {
        a += rhs.a;
        b += rhs.b;
        return *this;
    }
    
    complex &operator -= (const complex &rhs) {
        a -= rhs.a;
        b -= rhs.b;
        return *this;
    }
    
    complex &operator *= (const complex &rhs) {
        // Use the multiplication formula: (a + bi)(c + di) = (ac - bd) + (ad + bc)i
        double new_a = a * rhs.a - b * rhs.b;
        double new_b = a * rhs.b + b * rhs.a;
        a = new_a;
        b = new_b;
        return *this;
    }
    
    complex &operator /= (const complex &rhs) {
        double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
        
        // Check for division by zero (within epsilon)
        if (std::abs(rhs.a) < 1e-6 && std::abs(rhs.b) < 1e-6) {
            throw divided_by_zero();
        }
        
        double new_a = (a * rhs.a + b * rhs.b) / denominator;
        double new_b = (b * rhs.a - a * rhs.b) / denominator;
        a = new_a;
        b = new_b;
        return *this;
    }

    bool operator == (const complex &rhs) const { // 判断相等
        return std::abs(a - rhs.a) < 1e-6 && std::abs(b - rhs.b) < 1e-6;
    }
    
    explicit operator bool() const { // 转换为 bool
        return std::abs(a) >= 1e-6 || std::abs(b) >= 1e-6;
    }

    friend std::ostream &operator << (std::ostream &os, const complex &x) { // 输出
        // Set precision to 6 decimal places
        os << std::fixed << std::setprecision(6);
        
        // Handle real part
        if (x.a < -1e-6) {
            os << x.a;
        } else if (x.a > 1e-6) {
            os << x.a;
        } else {
            os << "0.000000";
        }
        
        // Handle imaginary part
        if (x.b < -1e-6) {
            os << "-" << std::abs(x.b) << "i";
        } else if (x.b > 1e-6) {
            os << "+" << x.b << "i";
        } else {
            os << "+0.000000i";
        }
        
        return os;
    }
};

}

#endif
