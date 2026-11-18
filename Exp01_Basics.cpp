#include <iostream>
using namespace std;

int main() {
    const double TAX = 0.18;
    string item;
    int qty;
    double price;

    cout << "Enter item, qty, price: ";
    cin >> item >> qty >> price;

    double total = (qty * price) * (1 + TAX);
    bool valid = (qty > 0 && price > 0);

    cout << "Item: " << item << " | Valid: " << boolalpha << valid << "\n";
    cout << "Total (with 18% tax): " << total << "\n";
    return 0;
}
