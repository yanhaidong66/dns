#pragma once
#include"config.h"


typedef struct query {
	char domain[30][30];
	char type;
	char query_class;
}query;



typedef struct requestionFrame
{
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

