#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
    int m,n,ans = 0;
    cin>>m>>n;
    int* schools = new int[m];
    int* students= new int[n];

    for(int i = 0; i < m; i++)
        scanf("%d",&(schools[i]));
    for(int i = 0; i < n; i++)
        scanf("%d",&(students[i]));

    sort(schools,schools + m);

    for(int i = 0; i < n; i++)//jurge students
    {
        int lower;
        lower = lower_bound(schools,schools+m,students[i]) - schools;
        //cout<<lower<<endl;
        if(lower == m )//bigger than max
            ans += students[i] - schools[lower-1];
        else{
            if(lower == 0)//lower than min
                ans += schools[lower] - students[i];
            else
                ans += min(abs(schools[lower]-students[i]),abs(schools[lower-1]-students[i]));
        }

    }
    cout<<ans;
    return 0;
}
