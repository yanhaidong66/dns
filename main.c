#include<stdlib.h>
#include<WinSock2.h>
#include<stdio.h>
#include"util.h"
#include"processFrame.h"
#include"config.h"
char ip_in_buff[MAX_BUFF_IP][MAX_LEN_IP];//从txt中读入的缓存ip
char domain_in_buff[MAX_BUFF_DOMAIN][MAX_LEN_DOMAIN];//从txt中读入的缓存域名
int main(void) {
	readFromTxt("dnsrelay.txt");
	WSADATA wsaData;
	SOCKET socketfd;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	char buff[BUFFER_SIZE] = { 0 };
	int clientAddrLen = sizeof(clientAddr);
	char frame[BUFFER_SIZE] = { 0 };

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
		perror("WSAStartup failed");
		return 1;
	}

	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketfd == INVALID_SOCKET) {
		perror("socket creation failed");
		return 1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(PORT);

	if (bind(socketfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		perror("bind failed");
		exit(1);
	}
	
	printf("dns server listening on port %d...\n", PORT);

	
	
	while (1) {
		int frameSize = recvfrom(socketfd, buff, sizeof(buff), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
 		toCharArrayHex(buff, frameSize,frame);
		/*打印帧的十六进制
		for (int i = 0; i<=frameSize; i++) {
			printf("%x", frame[i]);
		}*/
		printHexToBinary(frame, frameSize);
		
		if (frameSize < 0) {
			perror("Error in recvfrom");
			continue;
		}
		char return_frame[BUFFER_SIZE];
		frameSize = processFrame(frame, frameSize,return_frame);
		if (sendto(socketfd, return_frame, frameSize, 0, (const struct sockaddr*)&clientAddr, clientAddrLen) < 0) {
			perror("Error in sendto");
			exit(EXIT_FAILURE);
		}
		printf("-----------------------------------------------------------------------------------\n");
	}






	close(socketfd);
	return 1;

	

}