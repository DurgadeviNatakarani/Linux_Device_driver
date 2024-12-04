#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//function prototypes

int ADD(int,int);
int SUB(int,int);

struct cal
{
	int (*add)(int,int);
	int (*sub)(int,int);
};
int ADD(int a,int b)
{
	return a+b;
}
int SUB(int a,int b)
{
	return a-b;
}
struct cal var={.add=ADD,.sub=SUB,};
int main()
{
	int a,b;
	printf("enter a and b\n");
	scanf("%d %d",&a,&b);
	printf("%d\n",var.add(a,b));
}

	


