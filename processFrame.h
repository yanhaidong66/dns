#pragma once

#ifndef PROCESSFRAME
#define PROCESSFRAME
typedef struct response responseFrame;
typedef struct requestion requestionFrame;
int makeRespnseFrame(responseFrame* rpf, requestionFrame* rf);
responseFrame* processFrame(char frame[], int frameLen);


#endif // !PROCESSFRAME

