#include"head.h"
//ȫ�ֱ���
extern database db;


//�ַ�������
void toZero(char* s) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = '\0';
    }
}

//��txt�����һ������ת��Ϊip�Ͷ�Ӧ��domain
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

//��path�ж�ȡip��domain�洢��ȫ�ֱ���database db��
void readFromTxt(const char path[]) {
    FILE* file = fopen(path, "r"); // ���ļ�����ֻ��ģʽ��

    if (file == NULL) {
        printf("�޷����ļ�\n");
        exit(1);
    }

    // ��ȡ�ļ�����
    char line[500];
    fgets(line, sizeof(line), file);
    for (int i = 0; fgets(line, sizeof(line), file) != NULL; i++) {
        lineToIpAndDomain(line, db.ip[i], db.domain[i]);
        toZero(line);
        printf("%d:%s\n%s\n", i, db.ip[i], db.domain[i]);
    }


    fclose(file); // �ر��ļ�
}

void writeIntoTxt(const char path[]) {

}


void search(char domain[],char ip[]) {

}