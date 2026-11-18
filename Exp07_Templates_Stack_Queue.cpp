#include <iostream>
using namespace std;

template <typename T>
class Stack {
    T arr[5];
    int top = -1;
public:
    void push(T val) { if (top < 4) arr[++top] = val; }
    T pop() { return (top >= 0) ? arr[top--] : T(); }
};

int main() {
    Stack<int> s1; s1.push(10); s1.push(20);
    cout << "Int Pop: " << s1.pop() << "\n";

    Stack<float> s2; s2.push(3.14f); s2.push(9.8f);
    cout << "Float Pop: " << s2.pop() << "\n";

    Stack<string> s3; s3.push("Hello"); s3.push("C++");
    cout << "String Pop: " << s3.pop() << "\n";
    return 0;
}
