#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
/*struct st
{
	int key;
	int value;
};*/
int main()
{
	char s[50],i,p[20];
        int index;
	printf("enter key value pair\n");
	scanf("%[^\n]",s);
	//printf("enter index value\n");
//	scanf("%d",&index);
	int fd;
	fd=open("/dev/s_device",O_RDWR);
	if(fd<0)
		perror("open");
//        write(fd,&index,sizeof(int));
        write(fd,s,strlen(s)+1);
	read(fd,p,sizeof(p));
	printf("%s\n",p);

}

