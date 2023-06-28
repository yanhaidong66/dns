#include"head.h"

//全局变量区
database db;
int clientId_frameId[MAX_CLIENT][MAX_FRAME_FORWARD] ;//用户和没有在数据库找到的domain的帧id
SOCKET socketWithIsp;	//和因特网DNS服务商通信的socket
SOCKET socketWithClient;	//和用户通信的socket
struct sockaddr_in ispAddr;	//因特网DNS提供商的地址
struct sockaddr_in programeAddrToIsp;	//对于因特网DNS服务提供商，这个程序的地址
struct sockaddr_in programeAddrToClient;	//对于用户，这个程序的地址
struct sockaddr_in clientAddr;	//给这个程序发送请求的客户端的地址
int clientAddrLen;
int ispAddrLen;
myId id[MAX_CONVER_FRAME_SIZE];		////现在正在向上级dns转发的帧的自定义id数组
pthread_mutex_t mutex_id=PTHREAD_MUTEX_INITIALIZER;		//互斥锁


int main(void) {
	readFromTxt("dnsrelay.txt");
	WSADATA wsaData;
	clientAddrLen = sizeof(clientAddr);
	ispAddrLen = sizeof(ispAddr);
	//配置socket的启动项
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		perror("WSAStartup failed");
		return 1;
	}


	{
		//用户的地址需要每次接收到后设置
	}

	{// dns服务提供商 地址配置
		ispAddr.sin_family = AF_INET;//使用ipv4的协议族
		inet_pton(AF_INET, ISPADDR, &(ispAddr.sin_addr.s_addr));//我想要改为和特定ip通信的socket地址，这个ip是10.3.9.45将本地计算机的所有ip都和这个socket绑定
		ispAddr.sin_port = htons(PORT_ISP);//dns服务提供商的端口配置

	}

	{//   dns上级服务提供商的socket的配置
		programeAddrToIsp.sin_family = AF_INET;//使用ipv4的协议族
		programeAddrToIsp.sin_addr.s_addr = INADDR_ANY;//将本地计算机的所有ip都和这个socket绑定
		programeAddrToIsp.sin_port = htons(PORT_WITH_ISP);//端口配置
		socketWithIsp = socket(AF_INET, SOCK_DGRAM, 0);
		if (socketWithIsp == INVALID_SOCKET) {
			perror("socket creation failed");
			exit(1);
		}


		if (bind(socketWithIsp, (struct sockaddr*)&programeAddrToIsp, sizeof(programeAddrToIsp)) < 0) {
			perror("bind failed");
			exit(1);
		}

		//printf(" dns conected with ISP server listening on port %d...\n", PORT_WITH_ISP);
	}



	{//  这个程序对于客户的socket 地址配置
		programeAddrToClient.sin_family = AF_INET;//使用ipv4的协议族
		programeAddrToClient.sin_addr.s_addr = INADDR_ANY;//将本地计算机的所有ip都和这个socket绑定
		programeAddrToClient.sin_port = htons(PORT);//这个dns本地服务器的端口为PORT

		socketWithClient = socket(AF_INET, SOCK_DGRAM, 0);
		if (socketWithClient == INVALID_SOCKET) {
			perror("socket creation failed");
			return 1;
		}


		if (bind(socketWithClient, (struct sockaddr*)&programeAddrToClient, sizeof(programeAddrToClient)) < 0) {
			perror("bind failed");
			exit(1);
		}

		//printf(" dns conected with client server listening on port %d...\n", PORT);

	}

	

	//client_server_part
	pthread_t thread_id;
	int result = pthread_create(&thread_id, NULL, clientServerPart, NULL);
	if (result != 0) {
		//printf("无法创建线程，错误码：%d\n", result);
		return 1;
	}


	//ISP_server_part
		pthread_t thread_id1;
		int result1 = pthread_create(&thread_id1, NULL, ispServerPart, NULL);
		if (result1 != 0) {
			//printf("无法创建线程，错误码：%d\n", result1);
			return 1;
		}

	pthread_join(thread_id, NULL);
	pthread_join(thread_id1, NULL);


	


}