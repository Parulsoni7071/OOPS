#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    vector<int> marks = {72, 91, 65, 88};
    map<string, int> orderedMarks = {{"Aarav", 72}, {"Rohan", 91}};
    unordered_map<int, string> rollLookup = {{101, "Aarav"}, {102, "Rohan"}};

    sort(marks.begin(), marks.end());
    transform(marks.begin(), marks.end(), marks.begin(), [](int m) { return m + 5; });
    auto it = find_if(marks.begin(), marks.end(), [](int m) { return m > 90; });

    cout << "Sorted + Grace Marks: ";
    for (int m : marks) cout << m << " ";
    cout << "\nFirst Distinction (>90): " << (it != marks.end() ? *it : -1);
    cout << "\nMap (Aarav): " << orderedMarks["Aarav"] << " | Unordered (102): " << rollLookup[102] << "\n";
    return 0;
}
