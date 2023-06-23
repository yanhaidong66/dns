#pragma once
#ifndef CONFIG
#define CONFIG
#define BUFFER_SIZE 1024
#define PORT 53
#define MAX_LEN_IP 100
#define MAX_LEN_DOMAIN 100
#define MAX_BUFF_IP 1000
#define _CRT_SECURE_NO_WARNINGS
#define MAX_BUFF_DOMAIN 1000
extern char ip_in_buff[MAX_BUFF_IP][MAX_LEN_IP];
extern char domain_in_buff[MAX_BUFF_DOMAIN][MAX_LEN_DOMAIN];

#endif