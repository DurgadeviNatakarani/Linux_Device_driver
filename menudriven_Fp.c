//Implement a menu-driven program where each menu option is a separate function, and the menu is managed using function pointers.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int sum(int,int);
int sub(int,int);
int mul(int,int);
struct st
{
        int(*p)(int,int);//function pointer
};
int sum(int a,int b)
{
        return a+b;
}
int sub(int a,int b)
{
        return a-b;
}
int mul(int a,int b)
{
        return a*b;
}
int main()
{
        int a,b,n,c;
        char s[10];
        printf("enter a and b\n");
                      scanf("%d %d",&a,&b);//scanning a and b
        struct st v[3]={sum,sub,mul};/////array of structure
        printf("enter option 1)add 2)sub 3)mul\n");
        //scanf("%d",&n);///scanning option
        scanf("%s",s);
        if(strcmp(s,"sum")==0)//comparing input with function name
                n=1;
        else if(strcmp(s,"sub")==0)
                n=2;
        else if(strcmp(s,"mul")==0)
                n=3;

        switch(n)
        {
                case 1:c=v[n-1].p(a,b);//calling function through indices
                       break;
                case 2:c=v[n-1].p(a,b);
                       break;
                case 3:c=v[n-1].p(a,b);
                       break;
        }
        printf("%d\n",c);
}
