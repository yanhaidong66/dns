#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"config.h"
#include"util.h"
void printHexToBinary(char* hexArray, int length) {
    for (int i = 0; i < length; i++) {
        printHex(hexArray[i]);
    }
    printf("\n");
}

void printHex(char hex) {
    char c[8] = { 0 };
    for (int i = 0; i < 8; i++) {
        c[i] = hex;
    }
    c[7] = (c[7] & 0b10000000) >> 7;
    c[6] = (c[6] & 0b1000000) >> 6;
    c[5] = (c[5] & 0b100000) >>5;
    c[4] = (c[4] & 0b10000) >> 4;
    c[3] = (c[3] & 0b1000)>>3;
    c[2] = (c[2] & 0b100) >> 2;
    c[1] = (c[1] & 0b10) >> 1;
    c[0] = (c[0] & 0b1);
    printf(" ");
    for (int i = 0; i < 8; i++) {
        printf("%d", c[i]);
    }
    printf(" ");
}








void toHex(char ch,char* c1,char* c2) {
    (*c1)=(ch >> 4) & 0xF; 
    (*c2)= ch & 0xF; 
}
//存的是4位按照位存储的char，即：0000 0010这种
void toCharArrayHex(char arr[], int size, char* hexArray) {
    for (int i = 0; i < size; i++) {
        toHex(arr[i], &hexArray[2 * i], &hexArray[2 * i + 1]);
    }
}












