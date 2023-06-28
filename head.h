#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<WinSock2.h>
#include <pthread.h>
#include"config.h"
#include"database.h"
#include"processFrame.h"
#include"util.h"
void* clientServerPart();
void* ispServerPart();

//���ݽṹ����

typedef struct database {
	char ip[MAX_DATABSE_IP_COUNT][MAX_LEN_IP];//��txt�ж����ip���飬һά�±��domain��ͬ�����Ӧ
	char domain[MAX_DATABASE_DOMAIN_COUNT][MAX_LEN_DOMAIN];//��txt�ж����domain���飬һά�±��ip��ͬ�����Ӧ
	int size;	//databse�д洢��ip-domian������
	int nowSize;	//database��cache�д洢��ip��domain
}database;

typedef struct query {
	char domain[MAX_LEN_DOMAIN];
	char type;
	char query_class;
}query;



typedef struct requestion
{
	char frame[MAX_FRAME_SIZE];
	int sizeOfFrame;
	char ip[MAX_LEN_IP];
	char domain[MAX_LEN_DOMAIN];
	unsigned char id[5];
	unsigned char qr;
	unsigned char opcode;
	unsigned char aa;
	unsigned char tc;
	unsigned char rd;
	unsigned char ra;
	unsigned char rcode;
	unsigned int questionCount;
	unsigned int answerCount;
	unsigned int authorityCount;
	unsigned int additionCount;
	query queries[5];
}requestionFrame;

typedef struct response {
	char frame[MAX_FRAME_SIZE];
	int sizeOfFrame;
	unsigned char ip[MAX_LEN_IP];
	char domain[MAX_LEN_DOMAIN];
	unsigned char id[5];

}responseFrame;


typedef struct myId {
	char frameId[2];
	struct sockaddr_in addr;
}myId;

typedef struct {
	int count;
	int level;//���Եȼ�
	char dnsIp[40];
	char txtPath[100];
}Argv;

//ȫ�ֱ�����
extern database db;
extern int clientId_frameId[MAX_CLIENT][MAX_FRAME_FORWARD] ;
extern SOCKET socketWithIsp;	//��������DNS������ͨ�ŵ�socket
extern SOCKET socketWithClient;	//���û�ͨ�ŵ�socket
extern struct sockaddr_in ispAddr;	//������DNS�ṩ�̵ĵ�ַ
extern struct sockaddr_in clientAddr;	//���������������Ŀͻ��˵ĵ�ַ
extern int clientAddrLen;
extern struct sockaddr_in programeAddrToIsp;	//����������DNS�����ṩ�̣��������ĵ�ַ
extern struct sockaddr_in programeAddrToClient;	//�����û����������ĵ�ַ
extern int ispAddrLen ;		//isp�ĵ�ַ����
extern myId  id[MAX_CONVER_FRAME_SIZE];		//�����������ϼ�dnsת����֡���Զ���id�ṹ
extern pthread_mutex_t mutex_id;		//id�Ļ�����
extern pthread_mutex_t mutex_arg = PTHREAD_MUTEX_INITIALIZER;		//main�����Ĳ���������
extern Argv arg;	//main�Ĵ���Ĳ���



