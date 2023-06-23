#pragma once
#include"config.h"


typedef struct databse {
	char ip[MAX_DATABSE_IP_COUNT][MAX_LEN_IP];//从txt中读入的ip数组，一维下表和domain相同代表对应
	char domain[MAX_DATABASE_DOMAIN_COUNT][MAX_LEN_DOMAIN];//从txt中读入的domain数组，一维下表和ip相同代表对应
	int size;	//databse中存储的ip-domian的数量
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

