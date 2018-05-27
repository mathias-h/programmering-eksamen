#include <stdio.h>

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
                (b.m_real * a.m_imaginary - a.m_real * b.m_imaginary) / (pow(b.m_real, 2) + pow(b.m_imaginary,2))));
        }
        friend std::ostream& operator<<(std::ostream &out, const ComplexNumber &c)
        {
            out << c.m_real + " + i" + c.m_imaginary;
            return out;
        }
};

ComplexNumber getComplexNumber() {
    int real = -1, imaginay;

    while (real == -1) {
        if (scanf("%f + i%f", &real, &imaginay) != 2) {
            printf("invalid input, try again\n");
            real = -1;
        }
    }

    return ComplexNumber(real, imaginay);
}

int main() {
    char o;
    ComplexNumber a, b, r;

    while (1) {
        a = getComplexNumber();
        if (scanf("%c", &o) == 0) {
            cout << a;
        } else {
            b = getComplexNumber();

            switch (o) {
                case "+": r=a+b; break;
                case "-": r=a-b; break;
                case "*": r=a*b; break;
                case "/": r=a/b; break;
            }

            cout << r;
        }
    }
}