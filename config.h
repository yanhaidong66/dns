#pragma once


#ifndef CONFIG
#define CONFIG
#define MAX_CLIENT	10	//����û���
#define ISPADDR		"10.3.9.45"		//�ϼ�dns�������ĵ�ַ
#define MAX_FRAME_FORWARD	1000	//���ĳ���ͬʱ��dns������ת��֡�ĸ���
#define MAX_FRAME_SIZE 1024		//���պͷ��͵�֡������ֽ�
#define PORT 53		//���û�ͨ�ŵĶ˿�
#define PORT_WITH_ISP 5999		//��ispͨ�ŵĶ˿�
#define PORT_ISP 53			//dns�����ṩ�̵Ķ˿�
#define IP_ISP 10.3.9.45	//dns�����ṩ�̵�ip��ַ
#define MAX_LEN_IP 100
#define MAX_LEN_DOMAIN 100
#define MAX_DATABSE_IP_COUNT 1000			//database����ܴ洢��ip����
#define MAX_DATABASE_DOMAIN_COUNT 1000		//databse����ܴ洢��domain����
#define	MAX_CONVER_FRAME_SIZE 1024		//ͬʱת�����ϼ�dns��������֡����

#endif