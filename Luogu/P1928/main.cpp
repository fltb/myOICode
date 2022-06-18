#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

void rept (string &s);
int main()
{
    stack <string> sta;
    sta.push("");
    string ch;
    cin>>ch;
    for (int i = 0; i < ch.size(); i++)
    {
        switch (ch[i])
        {
            case '[' :{// empty string "" pushed
                        sta.push("");
                    }break;
            case ']' :{
                        string s_temp = sta.top();sta.pop();
                        rept(s_temp);
                        if (!sta.empty())
                        {
                            s_temp = sta.top() + s_temp;sta.pop();
                        }
                        sta.push(s_temp);
                    }break;
            default : sta.top() += ch[i];
        }
    }
    cout<<sta.top();
    return 0;
}
void rept (string &s)
{
    int times = 0;
    string str;
    if(s[0]>='0' && s[0]<='9')//set times num ,How TIAN_CAI(NAO_CAN) I am!
    {
        if(s[1]>='0' && s[1]<='9')
        {
            times = int((s[0] - '0')*10 + (s[1] - '0'));
            str = s.substr(2);
        }
        else
        {
            times = int(s[0] - '0');
            str = s.substr(1);
        }
    }
    s = "";
    for(int i = 0 ; i < times; i++)
        s += str;
}
