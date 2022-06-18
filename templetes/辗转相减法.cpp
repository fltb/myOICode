int gcv(int a,int b)
{
	if(a==b)
		return a;
	if(a>b)
		swap(a,b);
	return gcv(a,b-a);
}
