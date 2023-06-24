#pragma once

#ifndef PROCESSFRAME
#define PROCESSFRAME

int processFrame(char frame[], int frameLen, char return_frame[]);
int makeRespnseFrame(responseFrame* rpf, requestionFrame rf);

#endif // !PROCESSFRAME

