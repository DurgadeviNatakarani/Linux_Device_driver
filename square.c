//send a number to kernel from user space and kernel stores and square the data ,user reads and print that data
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
	char num[10];
	int fd,c;
	char res[10];
	printf("enter a number\n");
	scanf("%s",num);
	fd=open("/dev/simple_device",O_RDWR);
	if(fd<0)
		perror("open");
	write(fd,num,strlen(num)+1);
	c=read(fd,res,sizeof(res));
	res[c]=0;
        printf("%d\n",atoi(res));
}
