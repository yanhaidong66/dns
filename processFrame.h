#pragma once

#ifndef PROCESSFRAME
#define PROCESSFRAME

int processFrame(char buff[], int buffLen, char return_frame[]);
int makeRespnseFrame(responseFrame* responseFrame, requestionFrame requestionFrame);

#endif // !PROCESSFRAME

