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

//数据结构部分

typedef struct database {
	char ip[MAX_DATABSE_IP_COUNT][MAX_LEN_IP];//从txt中读入的ip数组，一维下表和domain相同代表对应
	char domain[MAX_DATABASE_DOMAIN_COUNT][MAX_LEN_DOMAIN];//从txt中读入的domain数组，一维下表和ip相同代表对应
	int size;	//databse中存储的ip-domian的数量
	int nowSize;	//database在cache中存储的ip和domain
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
	int level;//调试等级
	char dnsIp[40];
	char txtPath[100];
}Argv;

//全局变量区
extern database db;
extern int clientId_frameId[MAX_CLIENT][MAX_FRAME_FORWARD] ;
extern SOCKET socketWithIsp;	//和因特网DNS服务商通信的socket
extern SOCKET socketWithClient;	//和用户通信的socket
extern struct sockaddr_in ispAddr;	//因特网DNS提供商的地址
extern struct sockaddr_in clientAddr;	//给这个程序发送请求的客户端的地址
extern int clientAddrLen;
extern struct sockaddr_in programeAddrToIsp;	//对于因特网DNS服务提供商，这个程序的地址
extern struct sockaddr_in programeAddrToClient;	//对于用户，这个程序的地址
extern int ispAddrLen ;		//isp的地址长度
extern myId  id[MAX_CONVER_FRAME_SIZE];		//现在正在向上级dns转发的帧的自定义id结构
extern pthread_mutex_t mutex_id;		//id的互斥锁
extern pthread_mutex_t mutex_arg = PTHREAD_MUTEX_INITIALIZER;		//main函数的参数互斥锁
extern Argv arg;	//main的传入的参数



