//send a number to kernel from user space and kernel stores and square the data ,user reads and print that data
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	int fd,c,i;
	char s[30];
	char res[10];
	printf("enter a num and num1 and operation \n");
//	for(i=0;i<3;i++)
	scanf("%s",s);
	fd=open("/dev/simple_device",O_RDWR);
	if(fd<0)
		perror("open");
	write(fd,s,strlen(s)+1);
	c=read(fd,res,sizeof(res));
	res[c]=0;
        printf("%d\n",atoi(res));
}
