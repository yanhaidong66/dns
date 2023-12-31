#pragma once


#ifndef CONFIG
#define CONFIG
#define MAX_CLIENT	10	//最多用户数
#define ISPADDR		"202.106.0.20"		//上级dns服务器的地址
#define MAX_FRAME_FORWARD	2000	//最多的程序同时向dns服务器转发帧的个数
#define MAX_FRAME_SIZE 1024*2		//接收和发送的帧的最大字节
#define PORT 53		//和用户通信的端口
#define PORT_WITH_ISP 5999		//和isp通信的端口
#define PORT_ISP 53			//dns服务提供商的端口
#define MAX_LEN_IP 200
#define MAX_LEN_DOMAIN 200
#define MAX_DATABSE_IP_COUNT 2000			//database最多能存储的ip数量
#define MAX_DATABASE_DOMAIN_COUNT 2000		//databse最多能存储的domain数量
#define	MAX_CONVER_FRAME_SIZE 1024*2		//同时转发给上级dns服务器的帧个数

#endif