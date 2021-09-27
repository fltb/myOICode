#include <iostream>

using namespace std;

string trmid, trback;

void spt (int L1, int r1, int L2, int r2);
int main()
{
    cin>>trmid>>trback;
    spt(0, trmid.size() - 1, 0, trback.size() - 1);
    return 0;
}
void spt (int L1, int r1, int L2, int r2)
{

    int mid = trmid.find( trback[r2] );

    ///tests_begin//
    //cout<<endl<<"mid:"<<mid<<endl;
    ///tests_end

    cout<<trback[r2];

    ///tests_begin///////////////////
    //cout<<endl;
    //time++;
    //if(time == 10) exit(1);
    ///tests_end///////////////////

    if(L1 < mid){
        ////////////
        //cout<<"toleft"<<endl;
        spt(L1,mid - 1, L2 ,r2 - r1 + mid - 1);
    }
    if(r1 > mid){
        ////////////////
        //cout<<"toright"<<endl;
        spt(mid + 1 , r1 ,L2 - L1 + mid , r2 - 1);
    }
}
