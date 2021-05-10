#include <iostream>
#include <algorithm>

using namespace std;

int a[1000001],n;

void qsort (int l,int r);
int main()
{
    cin>>n;
    for(int i = 0; i < n; ++i)
    {
        cin>>a[i];
    }
    qsort(0,n-1);
    for(int i = 0; i < n; ++i)
    {
        cout<<a[i]<<" ";
    }
    return 0;
}
void qsort(int l,int r)
{
    if(r <= l)
    {
        return;
    }
    int mid = a[(l + r)/2];
    int i = l,j = r;
    do
    {
        while(a[i] < mid)
        {
            i++;
        }
        while(a[j] > mid)
        {
            j--;
        }
        if(i <= j)
        {
            swap(a[i],a[j]);
            i++;
            j--;
        }
    }while(i <= j);
    if(l<j) qsort(l,j);
    if(i<r) qsort(i,r);
}
