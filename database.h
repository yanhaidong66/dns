#pragma once
#ifndef DATABASE
#define DATABASE


//���е��ַ��������ԡ�\0����β��

void lineToIpAndDomain(char line[], char ip[], char domain[]);//��txt�ж����һ��ת��Ϊ��Ӧ��ip��domain
void readFromTxt(const char path[]);//��txt�ж���database��
void writeIntoTxt(const char path[]);//��ȫ�ֱ���database�е�ip��domain����dnsrelay.txtԭ�ȵĸ�ʽ����
int searchIp(char domain[],char ip[]);//��ȫ�ֱ���database�в���domain�����ҽ��������ip�ַ����У����û�ҵ���ipΪnull,����ҵ�����1���Ҳ�������0 
int addIpAndDomain(char domain[], char ip[]);//��ȫ�ֱ���database�в���һ��ip��domain�����ݣ������ӳɹ�����1��ʧ��0�������֮��Ҫ����txt�ļ���

#endif // !DATABASE

