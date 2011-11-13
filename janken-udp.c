#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

const int goo = 100;
const int choki = 101;
const int paa = 102;


int main(int argc, char**argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	char mesg[1000];
	int serverjanken[3] = {100,101,102};

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(1111);
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	for (;;)
	{
		len = sizeof(cliaddr);
		n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
		printf("recv:%d \n", mesg[0]);
		int i = rand()%3;
		int svjanken = serverjanken[i];
		if(mesg[0] == goo && svjanken == goo){
			printf("clinent:goo sv:goo");
		}	
		else if(mesg[0] == goo && svjanken == choki){
			printf("clinent:goo sv:choki");
		}	
		else if(mesg[0] == goo && svjanken == paa ){
			printf("clinent:goo sv:paa");
		}	
		sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
	}
}
