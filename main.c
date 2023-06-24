#include<WinSock2.h>
#include"head.h"
database db;
int main(void) {
	readFromTxt("dnsrelay.txt");
	WSADATA wsaData;
	SOCKET socketfd;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	char frame[MAX_FRAME_SIZE] = { 0 };

	{//配置socket


		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
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

	}
	









	//dns服务器主体
	while (1) {
		int frameSize = recvfrom(socketfd, frame, sizeof(frame), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);	
		if (frameSize < 0) {
			perror("Error in recvfrom");
			continue;
		}
		printCharToBinary(frame, frameSize);
		char return_frame[MAX_FRAME_SIZE];
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