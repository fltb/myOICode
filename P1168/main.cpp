#include <iostream>
#include <vector>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl; 
using std::vector;

int main() {
    std::ios::sync_with_stdio (false);
    int n;
    cin >> n;
    vector<int> V;
    int tmp;
    cin >> tmp;
    V.push_back(tmp);
    cout << tmp << endl;
    for (int i = 2; i <= n; i += 1) {
        int a1;
        cin >> a1;
        auto it = std::upper_bound(V.begin(), V.end(), a1);
        V.insert(it, a1);
        if ( (i+1) % 2 == 0) {
            cout << V[(i-1)/2] << endl; 
        }
    }
    return 0;
}
