#include"head.h"
//全局变量
extern database db;


//字符组清零
void toZero(char* s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = '\0';
    }
}

//从txt读入的一行数据转换为ip和对应的domain
void lineToIpAndDomain(char line[], char ip[], char domain[]) {
    int i = 0;
    for (i = 0; line[i] != ' '; i++) {
        ip[i] = line[i];
    }
    i++;
    for (int j = 0; line[i] != '\n' && line[i] != '\0'; i++, j++) {
        domain[j] = line[i];
    }
}

//从path中读取ip和domain存储到全局变量database db中
void readFromTxt(const char path[]) {
    FILE* file = fopen(path, "r"); // 打开文件，以只读模式打开

    if (file == NULL) {
        printf("无法打开文件\n");
        exit(1);
    }

    // 读取文件内容
    char line[500];
    fgets(line, sizeof(line), file);
    for (int i = 0; fgets(line, sizeof(line), file) != NULL; i++) {
        lineToIpAndDomain(line, db.ip[i], db.domain[i]);
        toZero(line);
        printf("%d:%s\n%s\n", i, db.ip[i], db.domain[i]);
    }


    fclose(file); // 关闭文件
}

void writeIntoTxt(const char path[]) {

}


void search(char domain[],char ip[]) {

}