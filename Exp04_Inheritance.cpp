#include <iostream>
using namespace std;

class Person {
public:
    string name;
    Person(string n) : name(n) {}
};

class Student : public Person {
public:
    int roll;
    Student(string n, int r) : Person(n), roll(r) {}
    void showStudent() { cout << "Student: " << name << ", Roll: " << roll << "\n"; }
};

class GraduateStudent : public Student {
public:
    string thesis;
    GraduateStudent(string n, int r, string t) : Student(n, r), thesis(t) {}
    void showGrad() { cout << "Grad: " << name << ", Roll: " << roll << ", Thesis: " << thesis << "\n"; }
};

int main() {
    Student s("Rohan", 101);
    GraduateStudent g("Priya", 502, "AI Security");
    s.showStudent();
    g.showGrad();
    return 0;
}
