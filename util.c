#include"head.h"
//全局变量
extern database db;


void printCharToBinary(char* a, int length) {
    for (int i = 0; i < length; i++) {
        printHex(a[i]);
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















