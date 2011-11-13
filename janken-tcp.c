#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const int BUFS = 512;

const int goo = 100;
const int choki = 101;
const int paa = 102;

const int win = 0;
const int lose = 1;
const int even = 2;

void err_func(char *msg)
{
	printf("errror.");
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	int sockfd, len, new_sockfd;
	char buf[BUFS];
	struct sockaddr_in serv, clt;
	socklen_t sin_siz;
	unsigned short port;
	int yes = 1;
	
	if(argc != 3)
	{
		printf("usage: progname ip port\n");
		exit(EXIT_FAILURE);
	}
	
	if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		err_func("socket");
	
	serv.sin_family = PF_INET;
	port = (unsigned short)atoi(argv[2]);
	serv.sin_port = htons(port);
	inet_aton(argv[1], &(serv.sin_addr));
	sin_siz = sizeof(struct sockaddr_in);
	
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof(yes));
	

	if(bind(sockfd, (struct sockaddr *)&serv, sin_siz) < 0)
		err_func("bind");
	
	if(listen(sockfd, SOMAXCONN) < 0)
		err_func("listen");
	
	while(1)
	{
		if((new_sockfd = accept(sockfd, (struct sockaddr *)&clt, &sin_siz)) < 0)
			err_func("accept");
		
		//printf("connect from %s : %u\n", inet_ntoa(clt.sin_addr), ntohs(clt.sin_port));
		printf("-----\n");
		memset(buf, 0, BUFS);
		printf("memseted\n");
		while(strncmp(buf, "EXIT\r\n", 6) != 0 && strncmp(buf, "EXIT\n", 5) != 0)
		{
			printf("recving\n");
			len = recv(new_sockfd, buf, BUFS, 0);
			buf[len] = '\0';
			printf("<- %s", buf);
			int svjanken = rand()%2 + goo;
			int judge = -1;

			if(buf[0] == goo && svjanken == goo){
				printf("clinent:goo sv:goo\n");
				judge = even;
			}	
			else if(buf[0] == goo && svjanken == choki){
				printf("clinent:goo sv:choki\n");
				judge = win;
			}	
			else if(buf[0] == goo && svjanken == paa ){
				printf("clinent:goo sv:paa\n");
				judge = lose;
			}	

	
			if(buf[0] == choki && svjanken == goo){
				printf("clinent:choki sv:goo\n");
				judge = lose;
			}	
			else if(buf[0] == choki && svjanken == choki){
				printf("clinent:choki sv:choki\n");
				judge = even;
			}	
			else if(buf[0] == choki && svjanken == paa ){
				printf("clinent:choki sv:paa\n");
				judge = win;
			}	

	
			if(buf[0] == paa && svjanken == goo){
				printf("clinent:paa sv:goo\n");
				judge = win;
			}	
			else if(buf[0] == paa && svjanken == choki){
				printf("clinent:paa sv:choki\n");
				judge = lose;
			}	
			else if(buf[0] == paa && svjanken == paa ){
				printf("clinent:paa sv:paa\n");
				judge = even;
			}	

			buf[0] = judge;
			buf[1] = svjanken;

			len = send(new_sockfd, buf, sizeof(buf), 0);
			printf("send\n");
		}
		close(new_sockfd);
	}
	close(sockfd);
	return 0;
}

