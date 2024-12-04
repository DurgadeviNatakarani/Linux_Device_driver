/implement a sorting fun that takes an array of ints and a comparison fun ptr to allow sorting in asce or desc
#include<stdio.h>
void (cp)(int,int);
void sort(int *,int);
int main()
{
	int n;
	printf("enter numberof elements\n");
	scanf("%d",&n);
	int a[n],i,j,k,l;
	printf("enter elements\n");
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	cp=sort;
	cp(a,n);
	for(i=0;i<n;i++)
		printf("%d ",a[i]);



}
void sort(int *a,int n)//////sorting function
{
	int i,j,k,l;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				k=a[j];
				a[j]=a[j+1];
				a[j+1]=k;
			}
		}
	}
}
