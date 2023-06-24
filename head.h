#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>
#include<stdlib.h>
#include"config.h"
#include"database.h"
#include"processFrame.h"
#include"util.h"


//���ݽṹ����

typedef struct database {
	char ip[MAX_DATABSE_IP_COUNT][MAX_LEN_IP];//��txt�ж����ip���飬һά�±��domain��ͬ�����Ӧ
	char domain[MAX_DATABASE_DOMAIN_COUNT][MAX_LEN_DOMAIN];//��txt�ж����domain���飬һά�±��ip��ͬ�����Ӧ
	int size;	//databse�д洢��ip-domian������
}database;

typedef struct query {
	char domain[MAX_QUERIES_COUNT][MAX_LEN_DOMAIN];
	char type;
	char query_class;
}query;



typedef struct requestionFrame
{
	char frame[MAX_FRAME_SIZE];
	int sizeOfFrame;
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

typedef struct responseFrame {
	char frame[MAX_FRAME_SIZE];
	int sizeOfFrame;

}responseFrame;

