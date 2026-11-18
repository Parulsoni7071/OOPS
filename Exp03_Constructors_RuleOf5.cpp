#include <iostream>
#include <algorithm>
using namespace std;

class Array {
    int* data;
    int size;
public:
    Array() : data(nullptr), size(0) { cout << "Default\n"; }
    Array(int s) : data(new int[s]{10, 20}), size(s) { cout << "Param\n"; }
    ~Array() { delete[] data; cout << "Destructor\n"; }

    Array(const Array& o) : data(new int[o.size]), size(o.size) {
        copy(o.data, o.data + size, data);
        cout << "Copy Const\n";
    }
    Array& operator=(const Array& o) {
        if (this != &o) {
            delete[] data; size = o.size;
            data = new int[size]; copy(o.data, o.data + size, data);
        }
        cout << "Copy Assign\n"; return *this;
    }
    Array(Array&& o) noexcept : data(o.data), size(o.size) {
        o.data = nullptr; o.size = 0; cout << "Move Const\n";
    }
    Array& operator=(Array&& o) noexcept {
        if (this != &o) {
            delete[] data; data = o.data; size = o.size;
            o.data = nullptr; o.size = 0;
        }
        cout << "Move Assign\n"; return *this;
    }
};

int main() {
    Array a1;
    Array a2(2);
    Array a3 = a2;
    a1 = a2;
    Array a4 = move(a2);
    a3 = move(a1);
    return 0;
}
