#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include"myheadSorting.h"

int main() {

	int csid, cid;
	char str[3000];
	int msgbyte, i;
	int max=3000, n=3000, a[3000];
	
	csid=socket(AF_INET, SOCK_STREAM, 0);
	if(csid == -1) {
		printf("IN SOCKET CREATION IN client SIDE FAILURE");
		exit(0);
	}
	printf("In socket creation in client side successful");
	
	struct sockaddr_in csadd;

	csadd.sin_family = AF_INET;
	csadd.sin_port = htons(7000);
	csadd.sin_addr.s_addr = inet_addr("127.0.0.1");
	int c = connect(csid, (struct sockaddr*)&csadd ,sizeof(csadd));
	if(c==0) {
		printf("connection establishment successful\n");
	}
	if(c==(-1)) {
		printf("connection establishment unsuccessful\n");
		exit(0);
	}

//send
	struct sockaddr_in sadd;
	sadd.sin_family = AF_INET;
	sadd.sin_port = htons(7000);
	sadd.sin_addr.s_addr = inet_addr("127.0.0.1");

	

	for(i=0; i<n; i++) {
		
		a[i] = rand() % 1000 + 1;
	}

	msgbyte = send(csid ,&a ,sizeof(a) ,0);
	for(i=0 ;i<3000; i++)
		printf("%d ", a[i]);

// recieve	
	struct sockaddr_in fadd;
	int len = sizeof(fadd);
	msgbyte = recv(csid, &a, sizeof(a), 0);
	for(i=0 ;i<3000; i++)
		printf("\n%d", a[i]);

	double cpu[4];
	recv(csid, cpu, sizeof(cpu), 0);
	
	printf("\nBubble sort takes %fsec\n", cpu[0]);
	printf("\nSelection sort takes %fsec\n", cpu[1]);
	printf("\nQuick sort takes %fsec\n", cpu[2]);
	printf("\nInsertion sort takes %fsec\n", cpu[3]);


	close(csid);
return 0;
}
