#pragma once

#ifndef PROCESSFRAME
#define PROCESSFRAME
typedef struct response responseFrame;
typedef struct requestion requestionFrame;
int makeRespnseFrame(responseFrame* rpf, requestionFrame* rf);
int processFrame(char frame[], int frameLen, char return_frame[]);


#endif // !PROCESSFRAME

