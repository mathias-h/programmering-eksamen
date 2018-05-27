#include <stdio.h>
#include <iostream>
#include <math.h>

class ComplexNumber {
    private:
        float m_real;
        float m_imaginary;
    public:
        ComplexNumber(float real, float imaginary): m_real(real), m_imaginary(imaginary) {}

        friend ComplexNumber operator+(ComplexNumber a, ComplexNumber b) {
            return ComplexNumber(
                a.m_real + b.m_real,
                a.m_imaginary + b.m_imaginary);
        }
        friend ComplexNumber operator-(ComplexNumber a, ComplexNumber b) {
            return ComplexNumber(
                a.m_real - b.m_real,
                a.m_imaginary - b.m_imaginary);
        }
        friend ComplexNumber operator*(ComplexNumber a, ComplexNumber b) {
            return ComplexNumber(
                a.m_real * b.m_real - a.m_imaginary * b.m_imaginary,
                a.m_real * b.m_imaginary + b.m_real * a.m_imaginary);
        }
        friend ComplexNumber operator/(ComplexNumber a, ComplexNumber b) {
            return ComplexNumber(
                (a.m_real * b.m_real + a.m_imaginary * b.m_imaginary) / (pow(b.m_real, 2) + pow(b.m_imaginary,2)),
                (b.m_real * a.m_imaginary - a.m_real * b.m_imaginary) / (pow(b.m_real, 2) + pow(b.m_imaginary,2)));
        }
        friend std::ostream& operator<<(std::ostream &out, const ComplexNumber &c)
        {
            out << c.m_real << " + i" << c.m_imaginary << "\n";
            return out;
        }
};

int main() {
    char o;
    float ra,rb,ia,ib;
    while (1) {
        std::cout << "Enter expression: ";

        if (scanf("%f+i%f %c %f+i%f", &ra, &ia, &o, &rb, &ib) != 5) {
            std::cout << "invalid expression\n";
        }

        ComplexNumber a(ra, ia);
        ComplexNumber b(rb, ib);

        switch (o) {
            case '+': std::cout << a+b; break;
            case '-': std::cout << a-b; break;
            case '*': std::cout << a*b; break;
            case '/': std::cout << a/b; break;
            default: std::cout << "invalid operator";
        }
    }
}