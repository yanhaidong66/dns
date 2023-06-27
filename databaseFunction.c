#include"head.h"
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
    int i = 0;
    for (i = 0; fgets(line, sizeof(line), file) != NULL; i++) {

        lineToIpAndDomain(line, db.ip[i], db.domain[i]);
        printf("%d:%s\n%s\n", i, db.ip[i], db.domain[i]);
        toZero(line);
        db.size = i + 1;
    }

    db.nowSize = db.size + 1;
    fclose(file); // 关闭文件
}



int searchIp(char domain[], char ip[]) {

    for (int i = 0; MAX_DATABSE_IP_COUNT > i; i++) {//逐行查找数据库中与domain匹配的IP,成功查找为1，同时被屏蔽的返回-1，查找失败返回0
        if (!strcmp(db.domain[i], domain)) {
            strcpy(ip, db.ip[i]);
            if (!strcmp(ip, "0.0.0.0")) {
                return -1;
            }
            return 1;
        }
    }

    return 0;
}



//从全局变量database中插入一条ip和domain的内容，如果添加成功返回1，失败0，如果cache已满，则替换最旧内容
int addIpAndDomain(char domain[], char ip[]) {

    if (MAX_DATABSE_IP_COUNT - 1 > db.nowSize) {
        for (int i = db.nowSize; i > db.size + 1; i--) {
            strcpy(db.ip[i], db.ip[i - 1]);
            strcpy(db.domain[i], db.domain[i - 1]);
        }
        db.nowSize++;
        strcpy(db.ip[db.size], ip);
        strcpy(db.domain[db.size], domain);
        return 1;

    }
    else {
        for (int i = MAX_DATABSE_IP_COUNT - 1; i > db.size; i--) {
            strcpy(db.ip[i], db.ip[i - 1]);
            strcpy(db.domain[i], db.domain[i - 1]);
        }
        strcpy(db.ip[db.size], ip);
        strcpy(db.domain[db.size], domain);
        return 1;
    }

    return 0;
}