#include <iostream>

using namespace std;

int main()
{
    string s1,s2;
    long long ans = 1;

    cin>>s1>>s2;
    for(int i = 0; i < s1.size(); i++){
        int cur = 0;
        for(int j = 0; j < s2.size(); j++){
            if(s1[i] == s2[j]){
                cur = j;
                break;
            }
        }
        if(cur != 0 && (s1[i + 1] == s2 [cur - 1]))
            ans*=2;
    }
    cout<<ans;
    return 0;
}
