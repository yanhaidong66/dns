#pragma once
#include"config.h"


typedef struct databse {
	char ip[MAX_DATABSE_IP_COUNT][MAX_LEN_IP];//��txt�ж����ip���飬һά�±��domain��ͬ�����Ӧ
	char domain[MAX_DATABASE_DOMAIN_COUNT][MAX_LEN_DOMAIN];//��txt�ж����domain���飬һά�±��ip��ͬ�����Ӧ
	int size;	//databse�д洢��ip-domian������
}database;

typedef struct query {
	char domain[30][30];
	char type;
	char query_class;
}query;



typedef struct requestionFrame
{
	char ip[MAX_QUERIES_COUNT][MAX_LEN_IP];
	char domain[MAX_QUERIES_COUNT][MAX_LEN_DOMAIN];
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

