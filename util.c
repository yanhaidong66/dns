#include"head.h"

void printCharToBinary(char* a, int length) {
    for (int i = 0; i < length; i++) {
        printBinary(a[i]);
    }
    //printf("\n");
}


void printBinary(char hex) {
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
    //printf(" ");
    for (int i = 7; i >=0; i--) {
        //printf("%d", c[i]);
    }
    //printf(" ");
}


void frameCopy(char destance[], char source[], int sourceLen) {
    for (int i = 0; i < sourceLen; i++) {
        destance[i] = source[i];
    }
}

void strCopy(char destance[], char source[]) {
    for (int i = 0; source[i]!='\0'; i++) {
        destance[i] = source[i];
    }
}


int stringToInt(char* s) {
    int t = 0;
    int r = 0;
    while (s[t]!='\0') {
        t++;
    }
    for (int i = t-1; i >= 0; i--) {
        int a = s[i];
        for (int j = i; j >= 0; j--) {
            a *= 10;
        }
        r += a;
    }
    return r;
}

int intToCharArray(char* arr, int num) {
    // 将整数转换为字符串
    char temp[12]; // 最大支持12位整数，包括符号和结尾的空字符
    int length = snprintf(temp, sizeof(temp), "%d", num);

    // 将字符串复制到字符数组中
    int i;
    for (i = 0; i < length; i++) {
        arr[i] = temp[i];
    }
    arr[length] = '\0'; // 在数组末尾添加空字符

    return length;
}












