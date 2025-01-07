///10,20,30,40--->2--->20,10,40,30
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
typedef struct st
{
	int rollno;
	char name[10];
	struct st *next;
}sll;
void add_begin(sll **);
void print_list(sll *);
int rev_list(sll *,int);
int main()
{
	sll* headptr=0;
	int c,op;
	while(1)
	{
		printf("enter choice\n 1)add_begin 2)print 3)rev_list\n");
		scanf("%d",&op);
                int n;
		switch(op)
		{
			case 1:add_begin(&headptr);
			       break;
			case 2:print_list(headptr);
			       break;
			case 3:printf("enter n value\n");
                               scanf("%d",&n);
                               rev_list(headptr,n);
			       break;
		}
	}
}
void add_begin(sll **ptr)
{
	sll *new=malloc(sizeof(sll));
	printf("enter data\n");
	scanf("%d %s",&new->rollno,new->name);
	new->next=*ptr;
	*ptr=new;
}
void  print_list(sll *ptr)
{
	int c=0;
	while(ptr)
	{
		c++;
		printf("%d %s\n",ptr->rollno,ptr->name);
		ptr=ptr->next;
	}
        printf("count of nodes =%d\n",c);
}
int rev_list(sll *ptr,int n)
{
	int c=0,i,j;
	if(ptr==0)
	{
		printf("data not found\n");
		return 0;
	}
	sll *p1=ptr,*p2,t;
	while(ptr)
	{
		c++;
		if(c==n)
		{

			for(i=0;i<c-1;i++)
			{
				p2=p1;
				for(j=0;j<c-i-1;j++)
				{
					p2=p2->next;
				}
				t.rollno=p1->rollno;
				strcpy(t.name,p1->name);	
				p1->rollno=p2->rollno;
				strcpy(p1->name,p2->name);
				p2->rollno=t.rollno;
				strcpy(p2->name,t.name);	
				p1=p1->next;
			}
			p1=ptr->next;
			c=0;
		}
		ptr=ptr->next;
	}    

}


