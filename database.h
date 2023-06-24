#pragma once
#ifndef DATABASE
#define DATABASE


//所有的字符串都是以’\0‘结尾的

void lineToIpAndDomain(char line[], char ip[], char domain[]);//从txt中读入的一行转换为对应的ip和domain
void readFromTxt(const char path[]);//从txt中读入database中
void writeIntoTxt(const char path[]);//将全局变量database中的ip和domain按照dnsrelay.txt原先的格式存入
int searchIp(char domain[],char ip[]);//从全局变量database中查找domain，并且将结果存入ip字符组中，如果没找到，ip为null,如果找到返回1，找不到返回0 
int addIpAndDomain(char domain[], char ip[]);//从全局变量database中插入一条ip和domain的内容，如果添加成功返回1，失败0，添加完之后要存入txt文件中

#endif // !DATABASE

