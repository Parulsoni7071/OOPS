#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) {}
    double area() override { return 3.14 * r * r; }
};

class Rectangle : public Shape {
    double l, w;
public:
    Rectangle(double l, double w) : l(l), w(w) {}
    double area() override { return l * w; }
};

class Triangle : public Shape {
    double b, h;
public:
    Triangle(double b, double h) : b(b), h(h) {}
    double area() override { return 0.5 * b * h; }
};

int main() {
    Shape* s[3] = { new Circle(5), new Rectangle(4, 6), new Triangle(3, 8) };
    for (int i = 0; i < 3; i++) {
        cout << "Area " << i + 1 << ": " << s[i]->area() << "\n";
        delete s[i];
    }
    return 0;
}
