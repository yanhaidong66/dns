#pragma once


#ifndef CONFIG
#define CONFIG
#define MAX_FRAME_SIZE 1024		//接收和发送的帧的最大字节
#define PORT 53
#define WITH_ISP_PORT 5999
#define MAX_LEN_IP 100
#define MAX_LEN_DOMAIN 100
#define MAX_DATABSE_IP_COUNT 1000			//database最多能存储的ip数量
#define MAX_DATABASE_DOMAIN_COUNT 1000		//databse最多能存储的domain数量
#define MAX_QUERIES_COUNT 5			//一个frame最多能包含几个dns请求

#endif