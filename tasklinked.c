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
sll *rev_linkn(sll*,int,int);
void middle_node(sll*);
void add_begin(sll **);
void print_list(sll *);
int rev_list(sll *,int);
void add_end(sll **);
void rev_print(sll *);
int count_node(sll *);
void sort_data(sll *);
void nth_nodeprint(sll *);
void nth_nodesingleloop(sll *ptr);
void nth_nodesingledel(sll **ptr);
void rot_loop(sll **);
void compare_list(sll*,sll*);
void del_pos(sll**);
void del_4thnode(sll **);
sll* reverseKGroup(sll* head, int k) ;
int main()
{
	sll* headptr=0;
	sll*head=0;
	int c,op;
	while(1)
	{
		printf("enter choice\n 1)add_begin 2)print 3)rev_list 4)add_end 5)count_node 6)rev_print 7)sort_data\n");
		scanf("%d",&op);
		int n;
		switch(op)
		{
			case 1:add_begin(&headptr);
			       break;
			case 16:add_begin(&head);
				break;
			case 2:print_list(headptr);
			       break;
			case 3:printf("enter n value\n");
			       scanf("%d",&n);
			       rev_list(headptr,n);
			       break;
			case 4:add_end(&headptr);
			       break;
			case 5:c=count_node(headptr);
			       break;
			case 6:rev_print(headptr);
			       break;
			case 7:sort_data(headptr);
			       break;
			case 8:nth_nodeprint(headptr);
			       break;
			case 9:nth_nodesingleloop(headptr);
			       break;
			case 10:nth_nodesingledel(&headptr);
				break;
			case 11:rot_loop(&headptr);
				break;
			case 12:rev_wlist(&headptr);
				break;
			case 13:even_node(headptr);
				break;
			case 14:middle_node(headptr);
				break;
			case 15:compare_list(headptr,head);
				break;
			case 17:copy_list(headptr,&head);
				print_list(head);
				break;
			case 18:del_pos(&headptr);
				break;
			case 19:del_4thnode(&headptr);
				break;
			case 20:last_nthnode(headptr);
				break;
			case 21:add_middle(&headptr);
				break;
			case 22:swap(2,4,&headptr);
				break;
			case 23:loop(headptr);
				break;
			case 24:int num,k,l;
			        l=count_node(headptr);
			        printf("enter nodes to be reversed\n");
			        scanf("%d",&k);
			        num=l/k;
			        printf("z=%d\n",num);
			        if(l>k)
			        {
				 headptr=rev_linkn(headptr,k,num);
			         }
			case 25:
			        printf("enter nodes to be reversed\n");
			        scanf("%d",&k);
				headptr=reverseKGroup(headptr, k); 
		}
	}
}
void middle_node(sll *ptr)
{
	sll *p1,*q,*r,*prev,*p2;
	p1=q=p2=ptr;
	int c=0,i,n;
	/*	while(q->next!=0)
		{
		if((q->next->next!=0))
		{
		p=p->next;
		q=q->next->next;
	// middle_node(q);
	}
	else
	q=q->next;
	}*/
	/*      while(q->next!=0) //1 2 3 4 -->1 3 4
		{
		if(q->next->next!=0)
		{
		r=p;
		p=p->next;
		q=q->next->next;
		}
		else
		q=q->next;
		}
		printf("middle node %d %s\n",p->rollno,p->name);
		r->next=p->next;
		free(p);*/
	while(p1)
	{
		c++;
		p1=p1->next;
	}
	n=c/2;
	for(i=0;i<c;i++) //1 2 3 4-->1 2 4
	{
		if(i==n)
		{
			prev->next=p2->next;
			free(p2);
		}

		prev=p2;
		p2=p2->next;
	}
}
void compare_list(sll*p,sll*q)
{
//	int flag=0
		while(p)
		{
			if(p->rollno !=q->rollno)
			{
				break;
			}
			p=p->next;
			q=q->next;
		}
	if(p==0)
		printf("lists are equal\n");
	else
		printf("lista are not equal\n");
}
void copy_list(sll *p,sll **q)
{
       sll*last=0;
	while(p)
	{
		sll *new=malloc(sizeof(sll));
		new->rollno=p->rollno;
		strcpy(new->name,p->name);
		new->next=0;
		if(*q==0)
			*q=new;
		else
			last->next=new;

		p=p->next;
		last=new;
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
int count_node(sll *ptr)
{
	int c=0;
	while(ptr)
	{
		c++;
		ptr=ptr->next;
	}
	return c;
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

			for(i=0;i<c;i++)
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
void add_end(sll **ptr)
{
	sll *new=malloc(sizeof(sll));
	printf("enter  a data\n");
	scanf("%d %s",&new->rollno,new->name);
	sll *last;
	/*	if(*ptr==0)
		{
	 *ptr=new;
	 }
	 else
	 {
	 last=*ptr;
	 while(last->next!=0)
	 last=last->next;
	 last->next=new;
	 }*/
	new->next=0;
	if(*ptr==0)
	{
		*ptr=new;
	}
	else
	{
		last=*ptr;
		while(last->next!=0)
			last=last->next;
		last->next=new;
	}
}
void rev_print(sll *ptr)
{
	int c=count_node(ptr),i,j;
	sll *p1=ptr,*p2;
	for(i=0;i<c;i++)
	{
		p2=p1;
		for(j=0;j<c-i-1;j++)
		{
			p2=p2->next;
		}
		printf("%d %s\n",p2->rollno,p2->name);
	}
}
void sort_data(sll *ptr)
{
	int c,i,j,k,l,t;
	sll *p1=ptr,*p2;
	c=count_node(ptr);
	char *s;
	for(i=0;i<c-1;i++)
	{
		p2=p1->next;
		for(j=0;j<c-i-1;j++)
		{
			if(p1->rollno>p2->rollno)
			{
				t=p1->rollno;
				strcpy(s,p1->name);
				p1->rollno=p2->rollno;
				strcpy(p1->name,p2->name);
				p2->rollno=t;
				strcpy(p2->name,s);
			}
			p2=p2->next;
		}
		p1=p1->next;
	}
}   
void nth_nodeprint(sll *ptr)
{
	int c=0;
        c=count_node(ptr);
        int i,j,k,l,n;
	printf("enter n node\n");
	scanf("%d",&n);
	j=c-n;
	for(i=0;i<c;i++)
	{
		if(i==j)
                {
			printf("%d %s\n",ptr->rollno,ptr->name);
                        printf("condition true\n");
                }
		ptr=ptr->next;
	}
}
void nth_nodesingleloop(sll *ptr)
{
	int n;
	printf("enter n node\n");
	scanf("%d",&n);
	sll *p1=ptr,*p2=ptr;
/*	while(p1)
	{
		n--;
		if(n<0)
			p2=p2->next;
		p1=p1->next;
	}*/
       while(p1)
       {
             n--;
             if(n<0)
             {
                p2=p2->next;
             }
           p1=p1->next;
       }
	printf("%d %s\n",p2->rollno,p2->name);
}
void nth_nodesingledel(sll **ptr)
{
	int n,c;
	printf("enter n node\n");
	scanf("%d",&n);
	sll *p1=*ptr,*p2=*ptr,*prev=*ptr;
	c=count_node(*ptr);
	/*        if(c==n)
		  {
	 *ptr=(*ptr)->next;
	// free(p1);
	return ;
	}
	while(p1)
	{
	n--;
	if(n<0)
	{
	prev=p2;
	p2=p2->next;
	}
	p1=p1->next;
	}
	prev->next=p2->next;
	free(p2);*/

	if(c==n)
	{
		p2=p1->next;
		free(p1);
		p1=0;
		return ;
	}
	while(p1!=0)
	{
		n--;
		if(n<0)
		{
			prev=p2;
			p2=p2->next;
		}
		p1=p1->next;

	}
	prev->next=p2->next;
	free(p2) ;
	//return del;
}
void rot_loop(sll **ptr)
{
	sll *p1=*ptr,*p2=*ptr,*t;
	int n,i,j,k;
	printf("enter n value\n");
	scanf("%d",&n);
	while(p1->next)               
	{
	        n--;
		if(n>0)
		{
			p2=p2->next;

		}
		p1=p1->next;
	}
        t=p2->next;
	p1->next=*ptr;
	*ptr=t;
	p2->next=0;
}  
void rev_wlist(sll **ptr)
{
	sll *p1=*ptr,*p2,*p3;
	if(p1->next==0)
	{
		printf("there are no records\n");
		return;
	}
/*	p2=p1->next
	while(p2)
	{
		p3=p2->next;
		p2->next=p1;
		p1=p2;
		p2=p3;
	}
	(*ptr)->next=0;
	*ptr=p1;*/
        p2=p1->next;
        while(p2)
        {
          p3=p2->next;
          p2->next=p1;
          p1=p2;
          p2=p3;
        }
        (*ptr)->next=0;
        (*ptr)=p1;
}


void even_node(sll *ptr)
{
	int i,j,c=count_node(ptr);
	int t;
	sll *ptr1;
	char s[10];
	for(i=0;i<c;i++)
	{
		ptr1=ptr;
		for(j=0;j<c-i-1;j++)
		{
			if((((ptr1->rollno) %2)!=0) && (((ptr1->next->rollno)%2)==0))
		{
				t=ptr1->rollno;
				strcpy(s,ptr1->name);
				ptr1->rollno=ptr1->next->rollno;
				strcpy(ptr1->name,ptr1->next->name);
				ptr1->next->rollno=t;
				strcpy(ptr1->next->name,s);
			}
			ptr1=ptr1->next;
		}
		ptr=ptr->next;
	}
}                
void node_del1(sll **ptr)
{
      sll *p,*q;
      p=*ptr;
      p->rollno=p->next->rollno;  
      strcpy(p->name,p->next->name);  
      p->next=p->next->next;
}
void del_pos(sll **ptr)
{
	sll *del=*ptr,*last,*prev;
	int c=count_node(*ptr),i,pos;
	printf("enter position\n");
	scanf("%d",&pos);
	for(i=1;i<=c;i++)
	{
		if(i==pos)
		{
			if(pos==1)
			{
				if(c==1)
				{
					*ptr=0;
					free(del);
					return;
				}
				else
				{
					*ptr=del->next;
					free(del);
				}
			}
			else
			{
				prev->next=del->next;
				free(del);
				return;
			}
		} 
		prev=del;
		del=del->next;
	}
}
void del_4thnode(sll **ptr)
{
    sll *del=*ptr,*prev;
    int c=0;
    while(del)
    {
          c++;
          if(c==4)
          {
             prev->next=del->next;
             free(del);
             return;       
          }
          prev=del;
          del=del->next;
   }
}
void last_nthnode(sll *ptr)
{
	int n;
	sll *p1=ptr,*p2=ptr,*prev;
	printf("enter n value\n");
	scanf("%d",&n);
	while(p1)
	{
		p1=p1->next;
		n--;
		if(n<0)
		{
                        prev=p2;
			p2=p2->next;
		}
	}
	printf("%d %s\n",p2->rollno,p2->name);
        prev->next=p2->next;
        free(p2);
        
}     
 void add_middle(sll **ptr)
{
   sll *new ,*last;
   new=malloc(sizeof(sll));
   scanf("%d%s",&new->rollno,new->name);
   if((*ptr==0)||((new->rollno) <((*ptr)->rollno)))
   {
            new->next=*ptr;
            *ptr=new;
   }
   else
   {
         last=*ptr;
         while((last->next!=0)&&((new->rollno)>(last->next->rollno)))
         last=last->next;
         new->next=last->next;
         last->next=new;
  }
}
void swap(int n1,int n2,sll **ptr)
{
	sll *p1,*p2,*prev,*prev1;
	p1=p2=*ptr;
	if(n1==n2)
	{
		printf("no need to swap\n");
		return;
	}
	int c=1;
	while((p1!=NULL) && (c<n1))
	{
		c++;
		prev=p1;
		p1=p1->next;
	}
	c=1;
	while((p2!=NULL) && (c<n2))
	{
		c++;
		prev1=p2;
		p2=p2->next;
	}
	prev->next=p2;
	prev1->next=p1;
	sll *t=p1->next;

	p1->next=p2->next;
	p2->next=t;
}

void loop(sll *ptr)
{
	sll *sp,*fp;
	sp=fp=ptr;
	/*	while((fp!=0)&&(fp->next!=0))   
		{
		sp=sp->next;
		fp=fp->next->next;
		if(sp==fp)
		{
		printf("loop found\n");
		return;
		}
		}*/
	while(fp!=0)
	{
		if((fp->next!=0)&&(fp->next->next!=0))
		{
			fp=fp->next->next;
			sp=sp->next;
		}
		if(sp==fp)
		{
			printf(" found\n");
			break;
		}
	}
}

sll * rev_linkn(sll* ptr, int k,int z) {
	if (!ptr)
		return NULL;

	sll* t = ptr,* p = NULL,* n = NULL;
	int count = 0;

	while (t != NULL && count < k) 
	{
		n = t->next; 
		t->next = p; 
		p = t;       
		t = n;       
		count++;
	}
	z--;
        printf ("%d %d %d\n",p->rollno,n->rollno,z); 
	if (n!=NULL && z>=1) 
	{
               printf ("%d %d %d\n",p->rollno,n->rollno,z); 
	ptr->next= rev_linkn(n, k,z);
	}
	else
	{	
		printf("enter into else:\n");
		sll * b=p;
		while(p->next!=NULL)
		{
			p=p->next;	
		}
		p->next=n;
		return b;
	}
	return p;
}
//middle node delete

/*struct ListNode* deleteMiddle(struct ListNode* head) {
 struct ListNode *p1,*p2,*prev,*del;
 p1=p2=del=head;
 int c=0,n,i;
 if(p1->next==0)
 {
    free(p1);
    p1=0;
    return p1;
 }
 while(p1)
 {
    c++;
    p1=p1->next;
 }
 n=c/2;
 for(i=0;i<c;i++)
 {
    if(i==n)
    {
          p1->next=prev->next;
          free(prev);
    }

     prev=p2;
     p2=p2->next;
    if(i==n)
    {
          prev->next=p2->next;
          free(p2);
    }

 }
 return del;

}*/
sll* reverseKGroup(sll* head, int k) {
    sll* current = head;
    sll* prev = NULL;
    sll* next = NULL;

    int count = 0;

    // First check if there are at least k nodes to reverse
    sll* temp = head;
    for (int i = 0; i < k; i++) {
        if (!temp) return head; // less than k nodes, return head as-is
        temp = temp->next;
    }

    // Reverse first k nodes
    while (current != NULL && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }

    // Now, next is pointing to (k+1)th node
    // Recurse for the list starting from current
    if (next != NULL)
        head->next = reverseKGroup(next, k);

    // prev is new head of reversed group
    return prev;
}

