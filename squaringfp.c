//WAP that reads an array of integers and applies a call back fun to each element to transform the values(doubling, squaring)
#include<stdio.h>
typedef int (*fp)(int);//typedefed function pointer
int sqr(int);
void callback(int ,fp);//callback function declaration
int main()
{
        int a[5],i;
        for(i=0;i<5;i++)
        {
                scanf("%d",&a[i]);//scanning array elements
        }
        for(i=0;i<5;i++)
        {
                callback(a[i],sqr);//calling callback function
        }
}
int sqr(int n)//square function definition
{
        return n*n;//returning result square of number
}
void callback(int a,fp  p)//callback function definition
{
         printf("%d ",p(a));
}
