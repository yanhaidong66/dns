#include"head.h"

//ȫ�ֱ�����
database db;
int clientId_frameId[MAX_CLIENT][MAX_FRAME_FORWARD] ;//�û���û�������ݿ��ҵ���domain��֡id
SOCKET socketWithIsp;	//��������DNS������ͨ�ŵ�socket
SOCKET socketWithClient;	//���û�ͨ�ŵ�socket
struct sockaddr_in ispAddr;	//������DNS�ṩ�̵ĵ�ַ
struct sockaddr_in programeAddrToIsp;	//����������DNS�����ṩ�̣��������ĵ�ַ
struct sockaddr_in programeAddrToClient;	//�����û����������ĵ�ַ
struct sockaddr_in clientAddr;	//���������������Ŀͻ��˵ĵ�ַ
int clientAddrLen;
int ispAddrLen;
myId id[MAX_CONVER_FRAME_SIZE];		////�����������ϼ�dnsת����֡���Զ���id����
pthread_mutex_t mutex_id=PTHREAD_MUTEX_INITIALIZER;		//������


int main(void) {
	readFromTxt("dnsrelay.txt");
	WSADATA wsaData;
	clientAddrLen = sizeof(clientAddr);
	ispAddrLen = sizeof(ispAddr);
	//����socket��������
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		perror("WSAStartup failed");
		return 1;
	}


	{
		//�û��ĵ�ַ��Ҫÿ�ν��յ�������
	}

	{// dns�����ṩ�� ��ַ����
		ispAddr.sin_family = AF_INET;//ʹ��ipv4��Э����
		inet_pton(AF_INET, ISPADDR, &(ispAddr.sin_addr.s_addr));//����Ҫ��Ϊ���ض�ipͨ�ŵ�socket��ַ�����ip��10.3.9.45�����ؼ����������ip�������socket��
		ispAddr.sin_port = htons(PORT_ISP);//dns�����ṩ�̵Ķ˿�����

	}

	{//   dns�ϼ������ṩ�̵�socket������
		programeAddrToIsp.sin_family = AF_INET;//ʹ��ipv4��Э����
		programeAddrToIsp.sin_addr.s_addr = INADDR_ANY;//�����ؼ����������ip�������socket��
		programeAddrToIsp.sin_port = htons(PORT_WITH_ISP);//�˿�����
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



	{//  ���������ڿͻ���socket ��ַ����
		programeAddrToClient.sin_family = AF_INET;//ʹ��ipv4��Э����
		programeAddrToClient.sin_addr.s_addr = INADDR_ANY;//�����ؼ����������ip�������socket��
		programeAddrToClient.sin_port = htons(PORT);//���dns���ط������Ķ˿�ΪPORT

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
		//printf("�޷������̣߳������룺%d\n", result);
		return 1;
	}


	//ISP_server_part
		pthread_t thread_id1;
		int result1 = pthread_create(&thread_id1, NULL, ispServerPart, NULL);
		if (result1 != 0) {
			//printf("�޷������̣߳������룺%d\n", result1);
			return 1;
		}

	pthread_join(thread_id, NULL);
	pthread_join(thread_id1, NULL);


	


}