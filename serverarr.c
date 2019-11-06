#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include <time.h>
#include"myheadSorting.h"


int main() {
	int ssid, cid, sid;
	char str[100];
	int msgbyte, a[5], n=5;

	
	ssid = socket(AF_INET,SOCK_STREAM,0);
	if(ssid == -1) {
		printf("IN SOCKET CREATION IN server SIDE FAILURE");
		exit(0);
	}
	printf("In socket creation in server side successful");

	struct sockaddr_in ssadd;
	ssadd.sin_family = AF_INET;
	ssadd.sin_port = htons(7000); 
	ssadd.sin_addr.s_addr = inet_addr("127.0.0.1");
	sid = bind(ssid,(struct sockaddr*)&ssadd,sizeof(ssadd));
	if(sid == -1){
		printf("\nBinding failure at server side");
		exit(0);
	}
	printf("\nBinding success at server side");

//listen optional
	listen(ssid,5);

//accept
	struct sockaddr_in fadd;
	int len = sizeof(fadd);
	int fd1 = accept(ssid,(struct sockaddr*)&fadd,&len);
	if(fd1 == (-1)) {
		printf("failure at server site in accept");
		exit(0);
	}

	clock_t start, end;
    double cpu_time_used[4];



//recieve
	msgbyte = recv(fd1, &a, sizeof(a), 0);

	int b[sizeof(a)], c[sizeof(a)], d[sizeof(a)];

	for(int i = 0; i < sizeof(a); ++i) {
		b[i]=a[i];
		c[i]=a[i];
		d[i]=a[i];
	}

	start = clock();
	bubbleSort(a, n);
	end = clock();
	cpu_time_used[0] = (((double) (end - start)) / CLOCKS_PER_SEC)* 1000;

	start = clock();
	selectionSort(b, n);
	end = clock();
	cpu_time_used[1] = (((double) (end - start)) / CLOCKS_PER_SEC)* 1000;

	start = clock();
	quickSort(c, 0, n - 1);
	end = clock();
	cpu_time_used[2] = (((double) (end - start)) / CLOCKS_PER_SEC)* 1000;

	start = clock();
	mergeSort(d, 0, n - 1);
	end = clock();
	cpu_time_used[3] = (((double) (end - start)) / CLOCKS_PER_SEC)* 1000;
	
//send
	msgbyte=send(fd1, &a, sizeof(a), 0);

	msgbyte=send(fd1, &cpu_time_used, sizeof(cpu_time_used), 0);
	
	printf("\nSorting algoriths processing complete and reports sent to client.\n");	

	close(ssid); 
return 0;
}
