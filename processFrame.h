#pragma once

#ifndef PROCESSFRAME
#define PROCESSFRAME
typedef struct response responseFrame;
typedef struct requestion requestionFrame;
int makeRespnseFrame(responseFrame* rpf, requestionFrame* rf);
int processFrame(char frame[], int frameLen, responseFrame* rpf,requestionFrame* rf);//����rf��rpf������ҵ�ip����ֵΪ1���Ҳ���Ϊ0
int getIpAndDomainFromFrame(responseFrame* rpf, int sizeOfFrame);//���ϼ�dns�ı�����ȡ��ip��domain

#endif // !PROCESSFRAME

