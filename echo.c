#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main()
{
	int fd,fd1;
	char s[10],p[10];
	fd=open("/dev/simple_device",O_RDWR,0664);
	if(fd<0)
		perror("open");
	printf("enter string \n");
	scanf("%s",s);
	write(fd,s,strlen(s));
	int c=read(fd,p,sizeof(p));
         p[c]='\0';
	printf("%s\n",p);
	close(fd);
}
