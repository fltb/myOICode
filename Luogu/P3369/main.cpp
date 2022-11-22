#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <iostream>
#include <utility>
using std::cin;
using std::cout;
typedef long long ll;
typedef std::pair<ll, ll> pll;
using namespace __gnu_pbds;
tree<pll, null_type, std::less<pll>, rb_tree_tag, tree_order_statistics_node_update> RBTree;
int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int act;
        ll k;
        cin >> act >> k;
        switch (act) {
        case 1:
            RBTree.insert(std::make_pair(k, i));
            break;
        case 2:
            RBTree.erase(RBTree.lower_bound(std::make_pair(k, -1)));
            break;
        case 3:
            cout << RBTree.order_of_key(std::make_pair(k, -1)) + 1 << '\n';
            break;
        case 4:
            cout << RBTree.find_by_order(k - 1)->first << '\n';
            break;
        case 5:
            cout << (--RBTree.lower_bound(std::make_pair(k, -1)))->first << '\n';
            break;
        case 6:
            cout << RBTree.lower_bound(std::make_pair(k, n))->first << '\n';
            break;
        }
    }
    return 0;
}