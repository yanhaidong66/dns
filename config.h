#pragma once


#ifndef CONFIG
#define CONFIG
#define MAX_CLIENT	10	//����û���
#define ISPADDR		"202.106.0.20"		//�ϼ�dns�������ĵ�ַ
#define MAX_FRAME_FORWARD	2000	//���ĳ���ͬʱ��dns������ת��֡�ĸ���
#define MAX_FRAME_SIZE 1024*2		//���պͷ��͵�֡������ֽ�
#define PORT 53		//���û�ͨ�ŵĶ˿�
#define PORT_WITH_ISP 5999		//��ispͨ�ŵĶ˿�
#define PORT_ISP 53			//dns�����ṩ�̵Ķ˿�
#define MAX_LEN_IP 200
#define MAX_LEN_DOMAIN 200
#define MAX_DATABSE_IP_COUNT 2000			//database����ܴ洢��ip����
#define MAX_DATABASE_DOMAIN_COUNT 2000		//databse����ܴ洢��domain����
#define	MAX_CONVER_FRAME_SIZE 1024*2		//ͬʱת�����ϼ�dns��������֡����

#endif