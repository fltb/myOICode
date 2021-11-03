#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void print(char a, char b) {
    cout << "Moved " << a << " to " << b << "\n";
}

void hanoi(int n, char a, char b, char c) {
    if (n == 1) {
        print(a, c);
    } else if (n > 1) {
        hanoi(n - 1, a, c, b);
        print(a, c);
        hanoi(n - 1, b, a, c);
    }
}

int main() {
    int n;
    cin >> n;
    hanoi(n, 'A', 'B', 'C');
    return 0;
}