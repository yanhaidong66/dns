#include"head.h"
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
    int i = 0;
    for (i = 0; fgets(line, sizeof(line), file) != NULL; i++) {

        lineToIpAndDomain(line, db.ip[i], db.domain[i]);
        printf("%d:%s\n%s\n", i, db.ip[i], db.domain[i]);
        toZero(line);
        db.size = i + 1;
    }

    db.nowSize = db.size + 1;
    fclose(file); // �ر��ļ�
}



int searchIp(char domain[], char ip[]) {

    for (int i = 0; MAX_DATABSE_IP_COUNT > i; i++) {//���в������ݿ�����domainƥ���IP,�ɹ�����Ϊ1��ͬʱ�����εķ���-1������ʧ�ܷ���0
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



//��ȫ�ֱ���database�в���һ��ip��domain�����ݣ������ӳɹ�����1��ʧ��0�����cache���������滻�������
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