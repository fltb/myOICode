#include <algorithm>
#include <cctype>
#include <cstdio>
#include <ios>
#include <iostream>
#include <string>
#include <tuple>
#define cosnt const
using std::cin;
using std::cout;
using std::get;
using std::make_tuple;
using std::string;
using std::tuple;
enum {
    INT,
    LONG,
    STRING,
    MXTYPE
};
const int SZ_TYPES[]{
    4, 8, 1};
const string TYPES[] = {
    "int",
    "long",
    "String"};
const int SZ_UP = 1024;
const string SZ_IND[] = {
    "B", "KB", "MB", "GB", "PB"};

/**
 * @brief resolve type
 *
 * @return std::tuple<int, bool> type isArray
 */
std::tuple<int, bool> resType() {
    string st;
    while (cin.peek() != ' ' && cin.peek() != '[') {
        st += cin.get();
    }
    int tp = -1;
    for (int i = 0; i < MXTYPE; i++) {
        if (st == TYPES[i]) {
            tp = i;
            break;
        }
    }
    if (tp == -1) {
        throw "INVALID TYPE: " + st;
    }
    if (cin.peek() == '[') {
        cin.get();
        cin.get();
        return make_tuple(tp, true);
    }
    return make_tuple(tp, false);
}
// ease the var name
void resVar() {
    while (cin.peek() != '=') {
        cin.get();
    }
}
/**
 * @brief return occupied length of the var
 *
 * @param tu
 * @return long long
 */
long long resVal(tuple<int, bool> tu) {
    long long len = 0;
    if (cin.peek() == '=') {
        cin.get();
    }
    if (get<1>(tu) == true) {
        // `=new [number]`
        while (cin.peek() != '[') {
            cin.get();
        }
        cin.get();
        cin >> len;
        cin.get();
    } else {
        switch (get<0>(tu)) {
        case INT:
        case LONG:
            long long tmp;
            cin >> tmp;
            len = 1;
            break;
        case STRING:
            cin.get();  // `="string"`
            while (cin.peek() != '"') {
                cin.get();
                len++;
            }
            cin.get();
            break;
        default:
            throw "UNKNOWN TYPE: " + std::to_string(get<0>(tu));
        }
    }
    return len;
}
void ptAns(long long ans, int dep) {
    if (ans <= 0 || dep > 3) {
        return;
    }
    ptAns(ans / SZ_UP, dep + 1);
    if (ans % SZ_UP > 0) {
        cout << ans % SZ_UP << SZ_IND[dep];
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    int n;
    cin >> n;
    cin.get();
    long long ans = 0;
    while (cin.good() && n > 0) {
        auto tu = resType();
        while (cin) {
            resVar();
            auto len = resVal(tu);
            ans += len * SZ_TYPES[get<0>(tu)];
            char ch;
            cin >> ch;
            if (ch == ';') {
                n--;
                cin.get();
                break;
            } else if (ch != ',') {
                throw "SOMETHING BAD HAPPEDNED!";
            }
        }
    }
    ptAns(ans, 0);
    cout << '\n';
    return 0;
}

/*
1
long[] a1=new int[1024],a2=new int[1024],a3=new int[1024];
*/