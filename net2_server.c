#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
main()
{
	int listfd,confd,retval;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	listfd=socket(AF_INET,SOCK_STREAM,0);
	childpid = fork();
	if(childpid == 0)
	{
		printf("...server enters into child process...\n");
		printf("child pid is:%d\n",getpid());
		if(listfd<0)
		{
			perror("sock:");
			exit(1);
		}
		bzero(&servaddr,sizeof(servaddr));
		servaddr.sin_family=AF_INET;
		servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
		servaddr.sin_port=htons(8000);
		retval=bind(listfd,(struct sockaddr *) &servaddr,sizeof(servaddr));
		if(retval<0)
		{
			perror("bind:");
			exit(2);
		}
		listen(listfd,5);
		while(1)
		{
			char buf[200];
			int n;
			clilen=sizeof(cliaddr);
			confd=accept(listfd,(struct sockaddr *)&cliaddr, &clilen);
			printf("client connected successfully...\n");
			n = read(confd,buf,200);
			buf[n] = '\0';
			printf("data received from client = %s\n",buf);
			write(confd,"Process ends",15);
		}
	}
	else
	{
		printf("Main process started..\n");
	}
}
