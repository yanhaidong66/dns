#pragma once

#ifndef PROCESSFRAME
#define PROCESSFRAME
typedef struct response responseFrame;
typedef struct requestion requestionFrame;
int makeRespnseFrame(responseFrame* rpf, requestionFrame* rf);
int processFrame(char frame[], int frameLen, responseFrame* rpf,requestionFrame* rf);//传入rf和rpf，如果找到ip返回值为1，找不到为0
int getIpAndDomainFromFrame(responseFrame* rpf, int sizeOfFrame);//从上级dns的报文中取出ip和domain

#endif // !PROCESSFRAME

