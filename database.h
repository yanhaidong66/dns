#pragma once
#ifndef DATABASE
#define DATABASE


void lineToIpAndDomain(char line[], char ip[], char domain[]);//从txt中读入的一行转换为对应的ip和domain
void readFromTxt(const char path[]);//从txt中读入database中
void writeIntoTxt(const char path[]);//将全局变量database中的ip和domain按照dnsrelay.txt原先的格式存入
void searchIp(char domain[],char ip[]);//从全局变量database中查找domain，并且将结果存入ip字符组中，如果没找到，ip为null


#endif // !DATABASE

