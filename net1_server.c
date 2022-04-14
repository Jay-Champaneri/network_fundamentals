#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<stdlib.h>
main()
{
	int sockfd,retval,n;
	char buf[2000];
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd<0)
	{
		perror("sock:");
		exit(1);
	}
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8000);
	retval=bind(sockfd,(struct sockaddr *) &servaddr,sizeof(servaddr));
	if(retval<0)
	{
		perror("bind:");
		exit(2);
	}
	clilen = sizeof(struct sockaddr_in);
	while(1)
	{
		n = recvfrom(sockfd, buf,10000,0,(struct sockaddr *)&cliaddr,&clilen);
		printf("received %d bytes\n",n);
		buf[n] = '\0';
		printf("Message from client = %s\n",buf);
	}
}
