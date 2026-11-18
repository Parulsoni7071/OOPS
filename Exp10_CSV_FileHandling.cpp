#include <iostream>
#include <fstream>
using namespace std;

int main() {
    fstream file("students.csv", ios::in | ios::out | ios::trunc);

    file << "Roll,Name,Marks\n";
    file << "101,Aarav,85\n";
    cout << "Write pointer (tellp): " << file.tellp() << "\n";

    file.seekp(-3, ios::cur);
    file << "95\n";

    file.seekg(0, ios::beg);
    cout << "Read pointer (tellg): " << file.tellg() << "\n\n--- CSV Records ---\n";

    string line;
    while (getline(file, line)) {
        cout << line << "\n";
    }

    file.close();
    return 0;
}
