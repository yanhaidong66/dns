#pragma once
#ifndef DATABASE
#define DATABASE


void lineToIpAndDomain(char line[], char ip[], char domain[]);//��txt�ж����һ��ת��Ϊ��Ӧ��ip��domain
void readFromTxt(const char path[]);//��txt�ж���database��
void writeIntoTxt(const char path[]);//��ȫ�ֱ���database�е�ip��domain����dnsrelay.txtԭ�ȵĸ�ʽ����
void searchIp(char domain[],char ip[]);//��ȫ�ֱ���database�в���domain�����ҽ��������ip�ַ����У����û�ҵ���ipΪnull


#endif // !DATABASE

