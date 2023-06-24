#include<WinSock2.h>
#include"head.h"
database db;
int main(void) {
	readFromTxt("dnsrelay.txt");
	WSADATA wsaData;
	SOCKET socketWithClient;
	SOCKET socketWithIsp;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	char frame[MAX_FRAME_SIZE] = { 0 };


	//配置socket的启动项
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
				perror("WSAStartup failed");
				return 1;
			}




	{//配置socketWithClient
		socketWithClient = socket(AF_INET, SOCK_DGRAM, 0);
		if (socketWithClient == INVALID_SOCKET) {
			perror("socket creation failed");
			return 1;
		}

		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		serverAddr.sin_port = htons(PORT);

		if (bind(socketWithClient, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
			perror("bind failed");
			exit(1);
		}

		printf(" dns conected with client server listening on port %d...\n", PORT);

	}


	{//配置socketWithIsp
		socketWithClient = socket(AF_INET, SOCK_DGRAM, 0);
		if (socketWithClient == INVALID_SOCKET) {
			perror("socket creation failed");
			return 1;
		}

		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		serverAddr.sin_port = htons(WITH_ISP_PORT);

		if (bind(socketWithClient, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
			perror("bind failed");
			exit(1);
		}

		printf(" dns conected with ISP server listening on port %d...\n", WITH_ISP_PORT);






	}
	









	//dns服务器主体
	while (1) {
		int frameSize = recvfrom(socketWithClient, frame, sizeof(frame), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);	
		if (frameSize < 0) {
			perror("Error in recvfrom");
			continue;
		}
		printCharToBinary(frame, frameSize);
		char return_frame[MAX_FRAME_SIZE];
		responseFrame* response = processFrame(frame, frameSize,return_frame);
		if (response == NULL) {
			if (sendto(socketWithClient, frame, frameSize, 0, (const struct sockaddr*)&clientAddr, clientAddrLen) < 0) {
				perror("Error in sendto");
				continue;
			}

			
			continue;
		}
		if (sendto(socketWithClient, response->frame, response->sizeOfFrame, 0, (const struct sockaddr*)&clientAddr, clientAddrLen) < 0) {
			perror("Error in sendto");
			exit(EXIT_FAILURE);
		}
		printf("-----------------------------------------------------------------------------------\n");
	}






	close(socketWithClient);
	return 1;

	

}