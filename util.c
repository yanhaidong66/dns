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
    char c[4] = { 0 };
    for (int i = 0; i < 4; i++) {
        c[i] = hex;
    }
    c[0] = c[0]>>3;
    c[1] = (c[1] & 0b100) >> 2;
    c[2] = (c[2] & 0b10) >> 1;
    c[3] = (c[3] & 0b1);
    printf(" ");
    for (int i = 0; i < 4; i++) {
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

void toZero(char* s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = '\0';
    }
}

void lineToIpAndDomain(char line[],char ip[],char domain[]) {
    int i = 0;
    for (i = 0; line[i] != ' '; i++) {
        ip[i] = line[i];
    }
    i++;
    for (int j=0; line[i] != '\n'&&line[i]!='\0'; i++, j++) {
        domain[j] = line[i];
    }
}
void readFromTxt(const char path[]) {
    FILE* file = fopen(path, "r"); // 打开文件，以只读模式打开

    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    // 读取文件内容
    char line[500];
    fgets(line, sizeof(line), file);
    for (int i = 0; fgets(line, sizeof(line), file) != NULL; i++) {
        lineToIpAndDomain(line, ip_in_buff[i], domain_in_buff[i]);
        toZero(line);
        //printf("%d:%s\n%s\n", i, ip_in_buff[i], domain_in_buff[i]);
    }
    

    fclose(file); // 关闭文件

    return 0;
}








