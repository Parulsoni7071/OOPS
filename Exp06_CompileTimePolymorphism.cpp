#include <iostream>
using namespace std;

class Complex {
public:
    int r, i;
    Complex(int r = 0, int i = 0) : r(r), i(i) {}
    void add(int x) { r += x; }
    void add(int x, int y) { r += x; i += y; }
    Complex operator+(const Complex& c) { return Complex(r + c.r, i + c.i); }
    void show() { cout << r << " + " << i << "i\n"; }
};

int main() {
    Complex c1(3, 2), c2(1, 4);
    Complex c3 = c1 + c2;
    c3.show();
    c1.add(5);
    c1.add(2, 3);
    c1.show();
    return 0;
}
